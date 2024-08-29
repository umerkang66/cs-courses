// "@tensorflow/tfjs-node": "^0.1.17",
process.env['TF_CPP_MIN_LOG_LEVEL'] = '2';
require('@tensorflow/tfjs-node');
const tf = require('@tensorflow/tfjs');
const loadCSV = require('./load-csv');

function knn(features, labels, predictionPoint, k) {
  const { mean, variance } = tf.moments(features, 0);

  // Calculating the standard deviation
  const scaledPredictionPoint = predictionPoint
    .sub(mean)
    .div(variance.pow(0.5));

  const scaledFeatures = features.sub(mean).div(variance.pow(0.5));

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

let { features, labels, testFeatures, testLabels } = loadCSV(
  'kc_house_data.csv',
  {
    shuffle: true,
    splitTest: 10,
    dataColumns: ['lat', 'long', 'sqft_lot, sqft_living'],
    labelColumns: ['price'],
  }
);

features = tf.tensor2d(features);
labels = tf.tensor2d(labels);

testFeatures.forEach((testFeature, i) => {
  const result = knn(features, labels, tf.tensor1d(testFeature), 10);
  const err = (testLabels[i][0] - result) / testLabels[i][0];

  // console.log('Guess:', result, ' Actual:', testLabels[i][0]);
  console.log(`Error ${err * 100} %`);
});
