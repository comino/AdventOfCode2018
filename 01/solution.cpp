#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using std::string; 
using std::vector;

/** @description reads the selected file into a std::vector<string> */
vector<string> readInputFile(const string fileName){
  auto inputFile = std::ifstream(fileName);
  auto line = string();
  auto returnVector = vector<string>();
  while( std::getline(inputFile, line) ){
    if( line.length() > 0){
      returnVector.push_back(line);
    }
  }
  return returnVector;
};

/** @description convert string array into a int array */
vector<int64_t> convertSringArrayToIntArray(const vector<string> stringArray){
  auto returnArray = vector<int64_t>();
  for( auto &s : stringArray){
    returnArray.push_back( std::stoi(s));
  }
  return returnArray;
};

int64_t solutionChallange01(){
  const auto frequencies = convertSringArrayToIntArray(readInputFile("input.txt"));
  return [&]() -> int64_t {
    int64_t sum = 0;
    for(auto &f: frequencies){ sum += f; }
    return sum;
  }();
}

int main(){
  auto solution = solutionChallange01();
  std::cout << "Solution: " <<  solution << "\n";
}

