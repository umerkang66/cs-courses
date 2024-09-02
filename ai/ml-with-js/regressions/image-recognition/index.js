process.env['TF_CPP_MIN_LOG_LEVEL'] = '2';
require('@tensorflow/tfjs-node');
const plot = require('node-remote-plot');
const mnist = require('mnist-data');
const LogisticRegression = require('./logistic-regression');

function loadData() {
  const mnistData = mnist.training(0, 60000);

  const features = mnistData.images.values.map(image => image.flatMap(x => x));

  const encodedLabels = mnistData.labels.values.map(label => {
    const row = new Array(10).fill(0);
    row[label] = 1;
    return row;
  });

  return { features, labels: encodedLabels };
}

const { features, labels } = loadData();

const regression = new LogisticRegression(features, labels, {
  learningRate: 1,
  iterations: 40,
  batchSize: 500,
});

regression.train();

function loadTestData() {
  const testMnistData = mnist.testing(0, 10000);
  const testFeatures = testMnistData.images.values.map(image =>
    image.flatMap(x => x)
  );
  const testEncodedLabels = testMnistData.labels.values.map(label => {
    const row = new Array(10).fill(0);
    row[label] = 1;
    return row;
  });

  return { testFeatures, testLabels: testEncodedLabels };
}

const { testFeatures, testLabels } = loadTestData();

const accuracy = regression.test(testFeatures, testLabels);
console.log('Accuracy:', accuracy);

// plot({
//   x: regression.costHistory.reverse(),
// });
