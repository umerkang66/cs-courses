const tf = require('@tensorflow/tfjs');

class LogisticRegression {
  // Mean and variance for feature standardization
  mean = null;
  variance = null;
  // History of cost (loss) for each iteration
  costHistory = [];

  /**
   * Create a new LogisticRegression model for multi-class classification (image recognition).
   * @param {Array|Tensor} features - The input features (X values).
   * @param {Array|Tensor} labels - The target values (one-hot encoded).
   * @param {Object} options - Training options (learningRate, iterations, batchSize).
   */
  constructor(features, labels, options) {
    // Standardize and add bias to features
    this.features = this.processFeatures(features);
    // Convert labels to tensor
    this.labels = tf.tensor2d(labels);
    // Initialize weights to zeros (one column per class)
    this.weights = tf.zeros([this.features.shape[1], this.labels.shape[1]]);

    // Set default options if not provided
    this.options = Object.assign(
      {
        learningRate: 0.1,
        iterations: 1000,
        batchSize: this.features.shape[0],
      },
      options
    );
  }

  /**
   * Perform one step of gradient descent to update weights.
   * @param {tf.Tensor} features - Batch of input features.
   * @param {tf.Tensor} labels - Batch of target values (one-hot encoded).
   * @returns {tf.Tensor} Updated weights.
   */
  gradientDescent(features, labels) {
    // Calculate predictions using the softmax function (multi-class)
    const currentGuesses = features.matMul(this.weights).softmax();
    // Calculate the difference between predictions and actual labels
    const differences = currentGuesses.sub(labels);

    // Calculate the gradient (slope) for each weight
    const slopes = features
      .transpose()
      .matMul(differences)
      .div(features.shape[0]);

    // Return updated weights (used with tf.tidy for memory management)
    return this.weights.sub(slopes.mul(this.options.learningRate));
  }

  /**
   * Train the model using batch gradient descent.
   */
  train() {
    // Calculate how many batches per epoch
    const batchQuantity = Math.floor(
      this.features.shape[0] / this.options.batchSize
    );

    for (let i = 0; i < this.options.iterations; i++) {
      for (let j = 0; j < batchQuantity; j++) {
        const bs = this.options.batchSize;

        // Use tf.tidy to manage memory for each batch
        this.weights = tf.tidy(() => {
          const featureSlice = this.features.slice([bs * j, 0], [bs, -1]);
          const labelSlice = this.labels.slice([bs * j, 0], [bs, -1]);

          // Update weights using this batch
          return this.gradientDescent(featureSlice, labelSlice);
        });
      }

      // Record the cost (loss) for this iteration
      this.recordCost();
      // Optionally adjust the learning rate
      this.updateLearningRate();
    }
  }

  /**
   * Make predictions for new observations (returns class index for each sample).
   * @param {Array|Tensor} observationsFeatures - New input data.
   * @returns {tf.Tensor} Predicted class index for each sample.
   */
  predict(observationsFeatures) {
    return this.processFeatures(observationsFeatures)
      .matMul(this.weights)
      .softmax()
      .argMax(1);
  }

  /**
   * Evaluate the model's accuracy on a test set.
   * @param {Array|Tensor} testFeatures - Features for testing.
   * @param {Array|Tensor} testLabels - True labels for testing (one-hot encoded).
   * @returns {number} Accuracy (fraction of correct predictions).
   */
  test(testFeatures, testLabels) {
    const predictions = this.predict(testFeatures);
    // Convert one-hot encoded labels to class indices
    testLabels = tf.tensor2d(testLabels).argMax(1);

    // Count the number of incorrect predictions
    const incorrect = predictions.notEqual(testLabels).sum().dataSync()[0];

    // Return accuracy (1 - fraction incorrect)
    return (predictions.shape[0] - incorrect) / predictions.shape[0];
  }

  /**
   * Standardize features and add a bias column (column of 1s).
   * @param {Array|Tensor} features - Input features.
   * @returns {tf.Tensor} Processed features.
   */
  processFeatures(features) {
    features = tf.tensor2d(features);

    // Standardize using mean and variance if already calculated
    if (this.mean && this.variance) {
      features = features.sub(this.mean).div(this.variance.pow(0.5));
    } else {
      features = this.standardize(features);
    }

    // Add a bias column (intercept term)
    features = tf.ones([features.shape[0], 1]).concat(features, 1);

    return features;
  }

  /**
   * Calculate and store the mean and variance for standardization.
   * @param {tf.Tensor} features - Input features.
   * @returns {tf.Tensor} Standardized features.
   */
  standardize(features) {
    const { mean, variance } = tf.moments(features, 0);

    this.mean = mean;
    // Add a small value to variance to avoid division by zero
    const filler = variance.cast('bool').logicalNot().cast('float32');
    this.variance = variance.add(filler);

    return features.sub(mean).div(this.variance.pow(0.5));
  }

  /**
   * Record the cost (cross-entropy loss) for the current weights.
   */
  recordCost() {
    const cost = tf.tidy(() => {
      const guesses = this.features.matMul(this.weights).softmax();

      const term1 = this.labels.transpose().matMul(guesses.add(1e-7).log());

      const term2 = this.labels
        .mul(-1)
        .add(1)
        .transpose()
        .matMul(guesses.mul(-1).add(1).add(1e-7).log());

      const cost = term1
        .add(term2)
        .div(this.features.shape[0])
        .mul(-1)
        .dataSync()[0];

      return cost;
    });

    this.costHistory.unshift(cost);
  }

  /**
   * Adjust the learning rate based on the trend of the cost.
   * If cost increases, decrease the learning rate. If it decreases, increase it slightly.
   */
  updateLearningRate() {
    if (this.costHistory.length < 2) {
      return;
    }

    const lastValue = this.costHistory[0];
    const secondLastValue = this.costHistory[1];

    if (lastValue > secondLastValue) {
      // Cost increased, decrease learning rate
      this.options.learningRate /= 2;
    } else {
      // Cost decreased, increase learning rate by 5%
      this.options.learningRate *= 1.05;
    }
  }
}

module.exports = LogisticRegression;
