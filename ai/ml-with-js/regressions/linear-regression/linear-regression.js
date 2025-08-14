const tf = require('@tensorflow/tfjs');

class LinearRegression {
  // Mean and variance for feature standardization
  mean = null;
  variance = null;
  // History of mean squared error (MSE) for each iteration
  mseHistory = [];

  /**
   * Create a new LinearRegression model.
   * @param {Array|Tensor} features - The input features (X values).
   * @param {Array|Tensor} labels - The target values (Y values).
   * @param {Object} options - Training options (learningRate, iterations, batchSize).
   */
  constructor(features, labels, options) {
    // Standardize and add bias to features
    this.features = this.processFeatures(features);
    // Convert labels to tensor
    this.labels = tf.tensor2d(labels);
    // Initialize weights to zeros
    this.weights = tf.zeros([this.features.shape[1], 1]);

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
   * @param {tf.Tensor} labels - Batch of target values.
   */
  gradientDescent(features, labels) {
    // Calculate predictions for current weights
    const currentGuesses = features.matMul(this.weights);
    // Calculate the difference between predictions and actual labels
    const differences = currentGuesses.sub(labels);

    // Calculate the gradient (slope) for each weight
    const slopes = features
      .transpose()
      .matMul(differences)
      .div(features.shape[0]);

    // Update weights using the learning rate
    this.weights = this.weights.sub(slopes.mul(this.options.learningRate));
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
        // Get a batch of features and labels
        const featureSlice = this.features.slice([bs * j, 0], [bs, -1]);
        const labelSlice = this.labels.slice([bs * j, 0], [bs, -1]);

        // Update weights using this batch
        this.gradientDescent(featureSlice, labelSlice);
      }

      // Record the mean squared error for this iteration
      this.recordMSE();
      // Optionally adjust the learning rate
      this.updateLearningRate();
    }
  }

  /**
   * Make predictions for new observations.
   * @param {Array|Tensor} observations - New input data.
   * @returns {tf.Tensor} Predicted values.
   */
  predict(observations) {
    return this.processFeatures(observations).matMul(this.weights);
  }

  /**
   * Evaluate the model using the R^2 (coefficient of determination) metric.
   * @param {Array|Tensor} testFeatures - Features for testing.
   * @param {Array|Tensor} testLabels - True labels for testing.
   * @returns {number} R^2 score (1 is perfect, 0 means no fit).
   */
  test(testFeatures, testLabels) {
    testFeatures = this.processFeatures(testFeatures);
    testLabels = tf.tensor2d(testLabels);

    // Make predictions for the test set
    const predictions = testFeatures.matMul(this.weights);

    // Calculate sum of squares of residuals and total sum of squares
    const SSres = testLabels.sub(predictions).pow(2).sum().dataSync()[0];
    const SStot = testLabels.sub(testLabels.mean()).pow(2).sum().dataSync()[0];

    // Return R^2 score
    return 1 - SSres / SStot;
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
    this.variance = variance;

    return features.sub(mean).div(this.variance.pow(0.5));
  }

  /**
   * Record the mean squared error (MSE) for the current weights.
   */
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

  /**
   * Adjust the learning rate based on the trend of the MSE.
   * If MSE increases, decrease the learning rate. If it decreases, increase it slightly.
   */
  updateLearningRate() {
    if (this.mseHistory.length < 2) {
      return;
    }

    const lastValue = this.mseHistory[0];
    const secondLastValue = this.mseHistory[1];

    if (lastValue > secondLastValue) {
      // MSE increased, decrease learning rate
      this.options.learningRate /= 2;
    } else {
      // MSE decreased, increase learning rate by 5%
      this.options.learningRate *= 1.05;
    }
  }
}

module.exports = LinearRegression;
