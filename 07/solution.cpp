#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <cstdlib>
#include <algorithm>
#include "./functional/functional.h"

using std::string; 
using std::vector;
using std::pair;
using std::unique_ptr;
using std::make_unique;
using std::cout;

//#define EXAMPLE_INPUT
#ifdef EXAMPLE_INPUT
static const string INPUT = "exampleInput.txt";
static const int numWorker = 2;
static const int charToIntConversion = 64;
#else
static const string INPUT = "input.txt";
static const int numWorker = 5;
static const int charToIntConversion = 4;
#endif

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
    vector<Node*> next;
    vector<Node*> prev;
    const char id; 

    int getRequired(){
      return ELI::reduce(prev, [](int acc, auto &b){ return !b->used? ++acc : acc;}, 0);
    };
    void setUsed(){
      this->used = true;
    };
    void setRunning(){
      this->running = true;
    }
    bool isRunning(){
      return running;
    }
    bool used = false;
    bool running = false;
};

class NodeTree {
  public:
    Node* find(const char c){
      for( auto &node : nodes){
        if( node->id == c) return node.get();
      }
      return nullptr;
    };

    Node* add(const pair<char,char> n){
      auto fromNode = find(n.first);
      auto toNode = find(n.second);
      if(!fromNode){
        nodes.push_back(make_unique<Node>(n.first));
        fromNode = find(n.first);
      }
      if(!toNode){ 
        nodes.push_back(make_unique<Node>(n.second));
        toNode = find(n.second);
      }
      fromNode->next.push_back(toNode);
      toNode->prev.push_back(fromNode);
    };

    auto getUnused(){
      return ELI::filter(getNodes(),[](auto n){return !n->used;});
    }
    auto getUnusedAndNoRequired(){
      return ELI::filter(getNodes(),[](auto n){return !n->used && !n->getRequired();});
    }

    auto getUnusedNoRequiredAndNotRunning(){
      return ELI::filter(getNodes(),[](auto n){return !n->used && !n->getRequired() && !n->isRunning();});
    }

    std::vector<Node*> getNodes(){
      return ELI::map(nodes, [](const auto &v){ return v.get();});
    }

    void setUsed(char c){
      find(c)->setUsed();
    }

  private:
    vector<unique_ptr<Node>> nodes = {};
};


string solutionPart1(){
  auto tree = NodeTree();
  auto nodes = getNodeEntries();
  for( auto &node : nodes){
    tree.add(node);
  }
  string solution = "";
  while( tree.getUnused().size()){
    const auto candidates = tree.getUnusedAndNoRequired();
    const auto nextNode = ELI::reduce(candidates, [](auto a, auto b){ return a && (a)->id <= (b)->id ? a : b; }, candidates[0] );
    tree.setUsed(nextNode->id);
    solution += nextNode->id;
  }
  return solution;
}

int solutionPart2(){

  vector<pair<int, Node*>> allWorkerBusyStatus(numWorker, std::make_pair(0, nullptr) );
  auto tree = NodeTree();
  auto nodes = getNodeEntries();
  for( auto &node : nodes){
    tree.add(node);
  }

  int count = 0;
  while(tree.getUnused().size()){
    count++;
    // process start of second
    for(auto &workerBusy: allWorkerBusyStatus){
      if(workerBusy.first == 0){ // non busy worker
        const auto readyToProcess = tree.getUnusedNoRequiredAndNotRunning();
        if(readyToProcess.size()){ // assign available task
          auto firstInAlphabet = [](auto a, auto b){ return a && (a)->id <= (b)->id ? a : b; } ;
          const auto nextNode = ELI::reduce(readyToProcess, firstInAlphabet, readyToProcess[0] );
          nextNode->setRunning();
          workerBusy.second = nextNode;
          workerBusy.first = ((int)(nextNode->id))-charToIntConversion;
        }
      }
    }
    // process end of second
    for(auto &workerBusy: allWorkerBusyStatus){
      if(workerBusy.first == 1 ){ // job done in next tick
        tree.setUsed(workerBusy.second->id);
        workerBusy.first = 0;
        workerBusy.second = nullptr;
      } else if(workerBusy.first > 0){ // tick
        --workerBusy.first;
      }
    }
  }
  return count;
}

int main(){
  auto sol1 = solutionPart1();
  std::cout << "Solution Part 1: " <<  sol1 << "\n";

  auto sol2 = solutionPart2();
  std::cout << "Solution Part 2: " <<  sol2 << "\n";
}


