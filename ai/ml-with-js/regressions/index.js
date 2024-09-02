// "@tensorflow/tfjs-node": "^0.1.17",
// "memoize": "^0.1.1",

process.env['TF_CPP_MIN_LOG_LEVEL'] = '2';
require('@tensorflow/tfjs-node');
const plot = require('node-remote-plot');

const loadCSV = require('./load-csv');
const LinearRegression = require('./linear-regression');

let { features, labels, testFeatures, testLabels } = loadCSV('./cars.csv', {
  shuffle: true,
  splitTest: 50,
  dataColumns: ['horsepower', 'weight', 'displacement'],
  labelColumns: ['mpg'],
});

const regression = new LinearRegression(features, labels, {
  // this will be adjusted automatically
  learningRate: 0.1,
  iterations: 30,
});

regression.train();
const R2 = regression.test(testFeatures, testLabels);

plot({
  x: regression.mseHistory.reverse(),
  xLabel: 'Iteration #',
  yLabel: 'Mean Squared Error',
});

console.log('R2:', R2);
