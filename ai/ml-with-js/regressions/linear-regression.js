const tf = require('@tensorflow/tfjs');
const _ = require('lodash');

class LinearRegression {
  m = 0;
  b = 0;

  // features and labels should be tensors
  constructor(features, labels, options) {
    this.features = features;
    this.labels = labels;

    // assign default values
    this.options = Object.assign(
      {
        learningRate: 0.1,
        iterations: 1000,
      },
      options
    );
  }

  gradientDescent() {
    const currentGuessesForMPG = this.features.map(row => {
      // mx + b
      return this.m * row[0] + this.b;
    });

    const slopeWithRespectToB =
      (_.sum(
        currentGuessesForMPG.map((guess, i) => {
          return guess - this.labels[i][0];
        })
      ) *
        2) /
      this.features.length;

    const slopeWithRespectToM =
      (_.sum(
        currentGuessesForMPG.map((guess, i) => {
          return -1 * this.features[i][0] * (this.labels[i][0] - guess);
        })
      ) *
        2) /
      this.features.length;

    // updating m and b; multiply by learning rate, and subtract with m and b respectively

    this.m = this.m - slopeWithRespectToM * this.options.learningRate;

    this.b = this.b - slopeWithRespectToB * this.options.learningRate;
  }

  train() {
    for (let i = 0; i < this.options.iterations; i++) {
      this.gradientDescent();
    }
  }
}

module.exports = LinearRegression;
