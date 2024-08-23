const IDropPosition = 0;
const IBounciness = 0;
const ISize = 0;
const IBucketLabel = 0;

const outputs = [];

function onScoreUpdate(dropPosition, bounciness, size, bucketLabel) {
  outputs.push([dropPosition, bounciness, size, bucketLabel]);

  console.log(outputs);
}

function runAnalysis() {
  // Write code here to analyze stuff
}
