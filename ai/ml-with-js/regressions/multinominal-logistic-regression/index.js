process.env['TF_CPP_MIN_LOG_LEVEL'] = '2';
require('@tensorflow/tfjs-node');

const loadCSV = require('../load-csv');
const LogisticRegression = require('./logistic-regression');

let { features, labels, testFeatures, testLabels } = loadCSV(
  '../data/cars.csv',
  {
    shuffle: true,
    splitTest: 50,
    dataColumns: ['horsepower', 'displacement', 'weight'],
    labelColumns: ['mpg'],
    converters: {
      mpg: value => {
        const mpg = parseFloat(value);
        if (mpg < 15) return [1, 0, 0];
        else if (mpg < 30) return [0, 1, 0];
        return [0, 0, 1];
      },
    },
  }
);

labels = labels.flatMap(x => x);
testLabels = testLabels.flatMap(x => x);

const regression = new LogisticRegression(features, labels, {
  // this will be adjusted automatically
  learningRate: 0.5,
  iterations: 20,
  batchSize: 50,
});

regression.train();
console.log('Correct:', regression.test(testFeatures, testLabels));
