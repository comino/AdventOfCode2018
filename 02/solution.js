let fs = require("fs");

const INPUT_FILE = "input.txt";
const MIN_COUNT_APPEARANCES = 2;
const MAX_COUNT_APPEARANCES = 3; 

function getFileContent(fileName) {
  return fs.readFileSync(fileName);
}

function countChars(inputString){
  let counter = {};
  [...inputString].forEach( c => counter[c]? counter[c]++ : counter[c]=1 );
  return counter; 
}

function compareIfStringDifferByOneChar(string1, string2){
  let differenceCounter = 0; 
  [...string1].forEach((c, index) => {
    if(string1[index] != string2[index]){
      if(++differenceCounter > 1) return false;
    }
  });
  return differenceCounter == 1;
}

function removeNotCommonChars(string1, string2){
  let returnString = "";
  [...string1].forEach((c, index) => {
    if(string1[index] == string2[index]){
      returnString += c;
    }
  });
  return returnString;
}

function solutionPart1() {
  const entries = getFileContent(INPUT_FILE).toString().split("\n");
  let accumulatedCounts = new Array(MAX_COUNT_APPEARANCES+1).fill(0);

  entries.forEach( entry => {
    const charCounter = countChars(entry);
    let doesAppearCounter = new Array(MAX_COUNT_APPEARANCES+1).fill(0);
    Object.keys(charCounter).forEach( letter => {
      if(charCounter[letter]>=MIN_COUNT_APPEARANCES && charCounter[letter] <= MAX_COUNT_APPEARANCES){
        doesAppearCounter[charCounter[letter]]=1;
      }
    });
    accumulatedCounts = accumulatedCounts.map((e, index) => accumulatedCounts[index]+doesAppearCounter[index]);
  });

  let product = 1;
  accumulatedCounts.forEach( c => c>0 && (product*=c));
  return product;
  
}

function solutionPart2() {
  const entries = getFileContent(INPUT_FILE).toString().split("\n");
  for( let first of entries){
    for( let second of entries){
      if( compareIfStringDifferByOneChar(first, second)){
        let sol =  removeNotCommonChars(first, second);
        return sol;
      }
    }
  }
}

console.log("Solution- Part1: " + solutionPart1());
console.log("Solution- Part2: " + solutionPart2());
