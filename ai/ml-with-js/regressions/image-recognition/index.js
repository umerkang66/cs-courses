// "@tensorflow/tfjs-node": "^0.1.17",
// "memoize": "^0.1.1",

process.env['TF_CPP_MIN_LOG_LEVEL'] = '2';
require('@tensorflow/tfjs-node');
const mnist = require('mnist-data');

const LogisticRegression = require('./logistic-regression');

const mnistData = mnist.training(0, 60000);

const features = mnistData.images.values.map(image => image.flatMap(x => x));

const encodedLabels = mnistData.labels.values.map(label => {
  const row = new Array(10).fill(0);
  row[label] = 1;
  return row;
});

const regression = new LogisticRegression(features, encodedLabels, {
  learningRate: 1,
  iterations: 20,
  batchSize: 100,
});

regression.train();

const testMnistData = mnist.testing(0, 1000);
const testFeatures = testMnistData.images.values.map(image =>
  image.flatMap(x => x)
);
const testEncodedLabels = testMnistData.labels.values.map(label => {
  const row = new Array(10).fill(0);
  row[label] = 1;
  return row;
});

const accuracy = regression.test(testFeatures, testEncodedLabels);
console.log('Accuracy:', accuracy);
