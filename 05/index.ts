import {readFileSync} from 'deno';

function getContent(fileName: string): string {
  const decoder = new TextDecoder('utf-8');
  return decoder.decode(readFileSync(fileName));
}


function removeMatchingChar( str: string) :string{
  let cstr = [...str];
  let i = 0;
  while(i< cstr.length-1){
    if( cstr[i+1] &&  cstr[i] && cstr[i] !== cstr[i+1]){
      if( cstr[i].toLowerCase() === cstr[i+1].toLowerCase() ){
        cstr.splice(i,2);
        i--;
        continue;
      }
    }
    i++;
  }
  return cstr.join("");
}

function solutionPart1(): void{
  const content = getContent("input.txt")
  const res = removeMatchingChar(content).trim().length;
  console.log("Solution Part1: " + res);
}

function solutionPart2(): void {
  const content = getContent("input.txt");
  let letters = Array.apply(null, {length: 26})
  .map(Number.call, Number)
  .map(e => String.fromCharCode(97 + e));

  letters = letters.map( letter => {
    let contentClipped = content
      .replace( new RegExp(letter.toLowerCase(), "g"), "")
      .replace( new RegExp(letter.toUpperCase(), "g"), "");
    return removeMatchingChar(contentClipped).trim().length;
  });
  console.log("Solution Part2: " + Math.min(...letters));
}

solutionPart1();
solutionPart2();



