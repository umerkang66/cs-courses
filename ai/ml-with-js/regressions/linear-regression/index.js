process.env['TF_CPP_MIN_LOG_LEVEL'] = '2';
require('@tensorflow/tfjs-node');
const plot = require('node-remote-plot');

const loadCSV = require('../load-csv');
const LinearRegression = require('./linear-regression');

let { features, labels, testFeatures, testLabels } = loadCSV(
  '../data/cars.csv',
  {
    shuffle: true,
    splitTest: 50,
    dataColumns: ['horsepower', 'weight', 'displacement'],
    labelColumns: ['mpg'],
  }
);

const regression = new LinearRegression(features, labels, {
  // this will be adjusted automatically
  learningRate: 0.1,
  iterations: 3,
  batchSize: 10,
});

regression.train();
// const R2 = regression.test(testFeatures, testLabels);
// console.log('R2:', R2);

// plot({
//   x: regression.mseHistory.reverse(),
//   xLabel: 'Iteration #',
//   yLabel: 'Mean Squared Error',
// });

regression
  .predict([
    [120, 2, 380],
    [135, 2.1, 420],
  ])
  .print();
