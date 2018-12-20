#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <cstdlib>
#include <algorithm>

using std::string; 
using std::vector;
using std::pair;
using std::unique_ptr;
using std::make_unique;

static const string INPUT = "exampleInput.txt";

/** @description reads the selected file into a std::vector<string> */
vector<string> readInputFile(const string fileName){
  auto inputFile = std::ifstream(fileName);
  auto line = string();
  auto returnVector = vector<string>();
  while( std::getline(inputFile, line)){
    if( line.length() > 0){
      returnVector.push_back(line);
    }
  }
  return returnVector;
};

vector<pair<char, char>> getNodeEntries(){
  const auto lines = readInputFile(INPUT);
  vector<pair<char,char>> returnVec = {};
  for( auto &line: lines){
    returnVec.push_back({line[5], line[36]});
  }
  return returnVec;
};


class Node {
  public: 
    Node(const char c):id(c){};
    vector<unique_ptr<Node>> next;
    vector<Node*> prev;
    char id; 

    Node* find(const char c){
      if(id==c){ 
        return this;
      }else{
        for( auto &n : next){
          const auto res = n->find(c);
          if(res){
            return res;
          }
        }
        return nullptr;
      }
    }

    Node* add(const pair<char,char> n){
      auto fromNode = find(n.first);
      auto toNode = find(n.second);
      if(!fromNode){
        fromNode = 
        next.push_back(make_unique<Node>(n.first));
        fromNode = find(n.first);
      }
      if(!toNode){
        fromNode->add(n);
      }else{
        fromNode->next.push_back(n);
      }
    }
};


int64_t solutionPart1(){
  auto nodes = getNodeEntries();
  return 1;
}

int64_t solutionPart2(){
  auto nodes = getNodeEntries();
  return 2;
}

int main(){
  auto sol1 = solutionPart1();
  std::cout << "Solution Part 1: " <<  sol1 << "\n";

  auto sol2 = solutionPart2();
  std::cout << "Solution Part 2: " <<  sol2 << "\n";
}

