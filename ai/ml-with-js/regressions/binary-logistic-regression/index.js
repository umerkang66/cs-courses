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
  iterations: 20,
  batchSize: 50,
  decisionBoundary: 0.5,
});

regression.train();
console.log('Correct:', regression.test(testFeatures, testLabels));

regression
  .predict([
    [130, 307, 1.75],
    [88, 97, 1.065],
  ])
  .print();

plot({
  x: regression.costHistory.reverse(),
  xLabel: 'Iteration #',
  yLabel: 'Cost',
});
