const outputs = [];

function onScoreUpdate(dropPosition, bounciness, size, bucketLabel) {
  // dropPosition, bounciness, size, bucket
  outputs.push([dropPosition, bounciness, size, bucketLabel]);
}

function runAnalysis() {
  const testSetSize = 100;
  // we have seen that the k=10, is the giving us the relatively more accurate results
  const k = 10;

  // TESTING WITH DIFFERENT K
  _.range(0, 3).forEach(feature => {
    const data = _.map(outputs, row => [row[feature], _.last(row)]);

    const [testSet, trainingSet] = splitDataset(minMax(data, 1), testSetSize);

    const accuracy = _.chain(testSet)
      .filter(
        testPoint =>
          knn(trainingSet, _.initial(testPoint), k) === _.last(testPoint)
      )
      .size()
      .divide(testSetSize)
      .value();

    console.log('For Feature:', feature, ', Accuracy:', accuracy);
  });
}

function knn(data, predictionPoint, k) {
  // predictionPoint is [300, .5, 16], it has all the metrics, except the bucket, which we will probability don't know when giving our own data for prediction (it will be known in the test data)
  return _.chain(data)
    .map(row => [distance(_.initial(row), predictionPoint), _.last(row)])
    .sortBy(row => row[0])
    .slice(0, k)
    .countBy(row => row[1])
    .toPairs()
    .sortBy(row => row[1])
    .last()
    .first()
    .parseInt()
    .value();
}

function distance(pointA, pointB) {
  // pointA=[300, .5, 16] pointB=[350, .55, 16]
  // zip will do this
  // [[300, 350], [.5, .55], [16, 16]]
  // n-dimensional pythagoras theorem
  return (
    _.chain(pointA)
      .zip(pointB)
      .map(([a, b]) => (a - b) ** 2)
      .sum()
      .value() ** 0.5
  );
}

function splitDataset(data, testCount) {
  const shuffled = _.shuffle(data);

  const testSet = _.slice(shuffled, 0, testCount);
  const trainingSet = _.slice(shuffled, testCount);

  return [testSet, trainingSet];
}

function minMax(data, featureCount) {
  // featureCount: how many columns we want to normalize
  const clonedData = _.cloneDeep(data);
  for (let j = 0; j < featureCount; j++) {
    const column = clonedData.map(row => row[j]);
    const min = _.min(column);
    const max = _.max(column);
    for (i = 0; i < clonedData.length; i++) {
      // min-max formula
      clonedData[i][j] = (clonedData[i][j] - min) / (max - min);
    }
  }
  return clonedData;
}
