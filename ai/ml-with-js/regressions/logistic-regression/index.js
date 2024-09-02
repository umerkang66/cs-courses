// "@tensorflow/tfjs-node": "^0.1.17",
// "memoize": "^0.1.1",

process.env['TF_CPP_MIN_LOG_LEVEL'] = '2';
require('@tensorflow/tfjs-node');
const plot = require('node-remote-plot');

const loadCSV = require('../load-csv');
const LogisticRegression = require('./logistic-regression');

let { features, labels, testFeatures, testLabels } = loadCSV(
  '../data/cars.csv',
  {
    shuffle: true,
    splitTest: 50,
    dataColumns: ['horsepower', 'displacement', 'weight'],
    labelColumns: ['passedemissions'],
    converters: {
      passedemissions: value => (value === 'TRUE' ? 1 : 0),
    },
  }
);

const regression = new LogisticRegression(features, labels, {
  // this will be adjusted automatically
  learningRate: 0.5,
  iterations: 100,
  batchSize: 50,
});

regression.train();
const correct = regression.test(testFeatures, testLabels);
console.log('Correct:', correct);

// plot({
//   x: regression.mseHistory.reverse(),
//   xLabel: 'Iteration #',
//   yLabel: 'Mean Squared Error',
// });

regression
  .predict([
    [130, 307, 1.75],
    [88, 97, 1.065],
  ])
  .print();
