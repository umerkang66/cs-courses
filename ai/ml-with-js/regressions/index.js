// "@tensorflow/tfjs-node": "^0.1.17",
// "lodash": "^4.17.11",
// "memoize": "^0.1.1",
// "mnist-data": "^1.2.6",
// "node-remote-plot": "^1.2.0",
// "shuffle-seed": "^1.1.6"
process.env['TF_CPP_MIN_LOG_LEVEL'] = '2';
require('@tensorflow/tfjs-node');
const tf = require('@tensorflow/tfjs');
const loadCSV = require('./load-csv');
const LinearRegression = require('./linear-regression');

let { features, labels } = loadCSV('./cars.csv', {
  shuffle: true,
  splitTest: 50,
  dataColumns: ['horsepower'],
  labelColumns: ['mpg'],
});

const regression = new LinearRegression(features, labels, {
  learningRate: 0.000001,
  iterations: 10000,
});

regression.train();
console.log('M:', regression.m, 'B:', regression.b);
