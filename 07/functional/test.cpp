#include "functional.h"
#include <iostream>
#include <vector>
#include <list>

using std::cout;
using std::vector;
using std::string;

int main(){

  std::vector<int> vec = {1,2,3,4,5,6};
  std::list<int> arr = {1,2,3};

  vec = filter( vec, [](auto &i){ return i>=2;});
  auto res2 = map(vec, [](auto &i){ return std::to_string(i) + "!" ;});

  std::cout <<  reduce(vec, [](int a, int b){ return a+b;}, 0)  << "\n";
  for(auto &v: res2){
    std::cout << v << " ";
  }
  std::cout << "\n";
  for(auto &v: arr){
    std::cout << v << " ";
  }
  std::cout << "\n";
}
