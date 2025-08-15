// "@tensorflow/tfjs-node": "^0.1.17",

// Suppress TensorFlow backend logs for cleaner output
process.env['TF_CPP_MIN_LOG_LEVEL'] = '2';
// require('@tensorflow/tfjs-node');
const tf = require('@tensorflow/tfjs');
const loadCSV = require('./load-csv');

/**
 * K-Nearest Neighbors (KNN) algorithm implementation.
 * Predicts the label for a given data point based on the k closest points in the dataset.
 * @param {tf.Tensor} features - The feature data (inputs) as a tensor.
 * @param {tf.Tensor} labels - The labels (outputs) as a tensor.
 * @param {tf.Tensor} predictionPoint - The point to predict for, as a tensor.
 * @param {number} k - The number of neighbors to consider.
 * @returns {number} The predicted label (average of k nearest neighbors).
 */
function knn(features, labels, predictionPoint, k) {
  // Calculate the mean and variance for each feature (column)
  const { mean, variance } = tf.moments(features, 0);

  // Standardize the prediction point using the mean and standard deviation
  const scaledPredictionPoint = predictionPoint
    .sub(mean)
    .div(variance.add(1e-10).pow(0.5));
  // Standardize all features in the dataset
  const scaledFeatures = features.sub(mean).div(variance.add(1e-10).pow(0.5));

  // Calculate the Euclidean distance between the prediction point and all other points
  // Then, sort by distance, take the k closest, and average their labels
  return (
    scaledFeatures
      .sub(scaledPredictionPoint)
      .pow(2)
      .sum(1)
      .pow(0.5)
      .expandDims(1)
      .concat(labels, 1)
      .unstack()
      .sort((a, b) => a.dataSync()[0] - b.dataSync()[0])
      .slice(0, k)
      .reduce((acc, currPair) => currPair.dataSync()[1] + acc, 0) / k
  );
}

// Load the dataset from CSV file
let { features, labels, testFeatures, testLabels } = loadCSV(
  'kc_house_data.csv',
  {
    shuffle: true, // Shuffle the data for randomness
    splitTest: 10, // Number of test samples
    dataColumns: ['lat', 'long', 'sqft_lot', 'sqft_living'], // Feature columns
    labelColumns: ['price'], // Label column
  }
);

// Convert features and labels to tensors
features = tf.tensor2d(features);
labels = tf.tensor2d(labels);

// Test the KNN algorithm on each test feature
testFeatures.forEach((testFeature, i) => {
  // Predict the price using KNN
  const result = knn(features, labels, tf.tensor1d(testFeature), 10);
  // Calculate the error percentage
  const err = (testLabels[i][0] - result) / testLabels[i][0];

  // Print the error for each prediction
  console.log(`Result: ${result}, `, `Error ${err * 100} %`);
});
