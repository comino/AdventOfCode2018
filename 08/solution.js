let fs = require("fs");

const INPUT_FILE = "input.txt";
const MIN_COUNT_APPEARANCES = 2;
const MAX_COUNT_APPEARANCES = 3; 

function getFileContent(fileName) {
  return fs.readFileSync(fileName)
    .toString()
    .trim()
    .split(" ")
    .map(e => parseInt(e));
}

const timeout = ms => new Promise(res => setTimeout(res, ms))

function evalNode(arr, sum){
  const numNodes = arr.shift();
  const numMeta = arr.shift();
  Array(numNodes).fill().forEach( e => { sum = evalNode(arr, sum) });
  Array(numMeta).fill().forEach( e => { sum += arr.shift() })
  return sum;
}

function evalNode2(arr, sum){
  const numNodes = arr.shift();
  const numMeta = arr.shift();
  if(numNodes) {
    let childW = Array(numNodes).fill().map( e => evalNode2(arr, sum));
    sum = 0;
    Array(numMeta).fill().forEach( e => {
      let index = arr.shift();
      sum += childW[index-1] ? childW[index-1]: 0;
    });
    return sum;
  }else{
    sum = 0;
    Array(numMeta).fill().forEach( e =>{ sum+=arr.shift()})
    return sum;
  }
}

function solutionPart1() {
  const entries = getFileContent(INPUT_FILE)
  return evalNode(entries, 0);
}

function solutionPart2() {
  const entries = getFileContent(INPUT_FILE)
  return evalNode2(entries, 0);
}
console.log("Solution- Part1: " + solutionPart1() ) ;
console.log("Solution- Part2: " + solutionPart2() ) ;

