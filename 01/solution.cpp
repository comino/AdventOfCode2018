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
  for(auto &s : stringArray){
    returnArray.push_back( std::stoi(s));
  }
  return returnArray;
};

int64_t solutionPart1(){
  const auto frequencies = convertSringArrayToIntArray(readInputFile("input.txt"));
  int64_t sum = 0;
  for(auto &f: frequencies){ sum += f; }
  return sum;
}

int64_t solutionPart2(){
  const auto frequencies = convertSringArrayToIntArray(readInputFile("input.txt"));
  auto frequencyHistory = vector<int64_t>();
  frequencyHistory.reserve(200000);
  int64_t currentSum = 0;

  while(true){
    for(auto &f: frequencies){ 
      currentSum += f;
      if( std::find( frequencyHistory.begin(), frequencyHistory.end(), currentSum )
          != frequencyHistory.end() ){
        return currentSum; 
      }
      frequencyHistory.push_back(currentSum);
    }
  }
}

int main(){
  std::cout << "Solution Part 1: " <<  solutionPart1() << "\n";
  std::cout << "Solution Part 2: " <<  solutionPart2() << "\n";
}

