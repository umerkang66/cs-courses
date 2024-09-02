const tf = require('@tensorflow/tfjs');

class LinearRegression {
  // we have two weights m and b
  mean = null;
  variance = null;
  mseHistory = [];

  // features and labels should be tensors
  constructor(features, labels, options) {
    this.features = this.processFeatures(features);
    this.labels = tf.tensor2d(labels);
    this.weights = tf.zeros([this.features.shape[1], 1]);

    // assign default values
    this.options = Object.assign(
      {
        learningRate: 0.1,
        iterations: 1000,
      },
      options
    );
  }

  gradientDescent() {
    const currentGuesses = this.features.matMul(this.weights);
    const differences = currentGuesses.sub(this.labels);

    const slopes = this.features
      .transpose()
      .matMul(differences)
      .div(this.features.shape[0]);

    this.weights = this.weights.sub(slopes.mul(this.options.learningRate));
  }

  train() {
    for (let i = 0; i < this.options.iterations; i++) {
      this.gradientDescent();
      this.recordMSE();
      this.updateLearningRate();
    }
  }

  test(testFeatures, testLabels) {
    testFeatures = this.processFeatures(testFeatures);
    testLabels = tf.tensor2d(testLabels);

    const predictions = testFeatures.matMul(this.weights);

    const SSres = testLabels.sub(predictions).pow(2).sum().dataSync()[0];
    const SStot = testLabels.sub(testLabels.mean()).pow(2).sum().dataSync()[0];

    return 1 - SSres / SStot;
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
    this.variance = variance;

    return features.sub(mean).div(this.variance.pow(0.5));
  }

  recordMSE() {
    const mse = this.features
      .matMul(this.weights)
      .sub(this.labels)
      .pow(2)
      .sum()
      .div(this.features.shape[0])
      .dataSync()[0];

    this.mseHistory.unshift(mse);
  }

  updateLearningRate() {
    if (this.mseHistory.length < 2) {
      return;
    }

    const lastValue = this.mseHistory[0];
    const secondLastValue = this.mseHistory[1];

    if (lastValue > secondLastValue) {
      // mse just increased, we are more incorrect, decrease the learning rate
      this.options.learningRate /= 2;
    } else {
      // increase by 5 percent
      this.options.learningRate *= 1.05;
    }
  }
}

module.exports = LinearRegression;
