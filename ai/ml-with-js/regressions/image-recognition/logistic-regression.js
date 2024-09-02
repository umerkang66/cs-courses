const tf = require('@tensorflow/tfjs');

class LogisticRegression {
  // we have two weights m and b
  mean = null;
  variance = null;
  costHistory = [];

  // features and labels should be tensors
  constructor(features, labels, options) {
    this.features = this.processFeatures(features);
    this.labels = tf.tensor2d(labels);
    this.weights = tf.zeros([this.features.shape[1], this.labels.shape[1]]);

    // assign default values
    this.options = Object.assign(
      {
        learningRate: 0.1,
        iterations: 1000,
        batchSize: this.features.shape[0],
      },
      options
    );
  }

  gradientDescent(features, labels) {
    const currentGuesses = features.matMul(this.weights).softmax();
    const differences = currentGuesses.sub(labels);

    const slopes = features
      .transpose()
      .matMul(differences)
      .div(features.shape[0]);

    this.weights = this.weights.sub(slopes.mul(this.options.learningRate));
  }

  train() {
    const batchQuantity = Math.floor(
      this.features.shape[0] / this.options.batchSize
    );

    for (let i = 0; i < this.options.iterations; i++) {
      for (let j = 0; j < batchQuantity; j++) {
        const bs = this.options.batchSize;
        const featureSlice = this.features.slice([bs * j, 0], [bs, -1]);
        const labelSlice = this.labels.slice([bs * j, 0], [bs, -1]);

        this.gradientDescent(featureSlice, labelSlice);
      }

      this.recordCost();
      this.updateLearningRate();
    }
  }

  predict(observationsFeatures) {
    return this.processFeatures(observationsFeatures)
      .matMul(this.weights)
      .softmax()
      .argMax(1);
  }

  test(testFeatures, testLabels) {
    const predictions = this.predict(testFeatures);
    testLabels = tf.tensor2d(testLabels).argMax(1);

    const incorrect = predictions.notEqual(testLabels).sum().dataSync()[0];

    return (predictions.shape[0] - incorrect) / predictions.shape[0];
  }

  processFeatures(features) {
    features = tf.tensor2d(features);

    if (this.mean && this.variance) {
      features = features.sub(this.mean).div(this.variance.pow(0.5));
    } else {
      features = this.standardize(features);
    }

    features = tf.ones([features.shape[0], 1]).concat(features, 1);

    return features;
  }

  standardize(features) {
    const { mean, variance } = tf.moments(features, 0);

    this.mean = mean;
    // this.variance = variance.add(tf.scalar(1e-7)); // Add a small epsilon to avoid division by zero

    // OTHER METHOD
    const filler = variance.cast('bool').logicalNot().cast('float32');
    this.variance = variance.add(filler);

    return features.sub(mean).div(this.variance.pow(0.5));
  }

  recordCost() {
    const guesses = this.features.matMul(this.weights).softmax();

    const term1 = this.labels.transpose().matMul(guesses.log());

    const term2 = this.labels
      .mul(-1)
      .add(1)
      .transpose()
      .matMul(guesses.mul(-1).add(1).log());

    const cost = term1
      .add(term2)
      .div(this.features.shape[0])
      .mul(-1)
      .dataSync()[0];

    this.costHistory.unshift(cost);
  }

  updateLearningRate() {
    if (this.costHistory.length < 2) {
      return;
    }

    const lastValue = this.costHistory[0];
    const secondLastValue = this.costHistory[1];

    if (lastValue > secondLastValue) {
      // mse just increased, we are more incorrect, decrease the learning rate
      this.options.learningRate /= 2;
    } else {
      // increase by 5 percent
      this.options.learningRate *= 1.05;
    }
  }
}

module.exports = LogisticRegression;
