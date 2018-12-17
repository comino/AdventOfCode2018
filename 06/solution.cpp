#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <cstdlib>
#include <algorithm>

using std::string; 
using std::vector;

class Point {
  public:
    Point(int x, int y): x(x), y(y) {};
    Point(std::string s): 
      x(std::stoi(s.substr(0, s.find(", ")))),
      y(std::stoi(s.substr(s.find(", ")+2))){};

    int distanceTo(const Point &p ){
      return abs(x - p.x) + abs( y - p.y);
    };
    std::string toString() const{
      return std::string(std::to_string(x) + std::string(", ") + std::to_string(y));
    }
    const int x;
    const int y;
};

class Field {
  public: 
    Field( int size):
      _size(size), 
      _field(size, vector<char>(size, '.')){}

    bool addPoint(const Point p, char id) {
      _dest.push_back({p, id});
      _field[p.y][p.x] = id;
    }

    bool print(){
      for(auto &row : _field){
        for( auto &entry : row){
          std::cout << entry << " ";
        }
        std::cout << "\n";
      }
    }
    void printDest(){
      std::cout << "\n";
      for(auto &p: _dest){
        std::cout << p.second << ": " << p.first.toString() << "\n";
      }
    }

    bool calcShortestDistance(){
      for(int row=0; row < _size; row++){
        for(int col=0; col < _size; col++){
          auto distances = std::vector<int>();

          // actually the second loop through can be saved by accumulating max dist while calc dist, 
          // this approach is less efficient, but more readable
          for( auto &p :_dest){
            const int d = p.first.distanceTo(Point(row,col));
            distances.push_back(d);
          }
          auto maxDist = std::min_element(distances.begin(), distances.end());
          auto maxVal = _dest[std::distance(distances.begin(),maxDist)].second;
          int numMaxVal = 0;
          for(auto &v : distances){
            if(v== *maxDist) numMaxVal++;
          }
          if( numMaxVal == 1){
            _field[col][row] = maxVal;
          }
        }
      }
    }

    vector<int> getAreas(){
      auto inf = getAllInfinite();
      vector<int> areas = {};
      for(auto &p: _dest){
        // if point not in inf, calc area
        if( std::find(inf.begin(), inf.end(), p.second) == inf.end()){
          int count = 0;
          for(auto &row: _field){
            for(auto &e: row){
              if( e == p.second){
                count++;
              }
            }
          }
          areas.push_back(count);
        }
      }
      return areas;
    }


  private:
    vector<char> getAllInfinite(){
      // a area is infinite if the selected char is on the edge
      auto addIfNotAlreadyAdded = [](vector<char> *v, char e){
        if( std::find(v->begin(), v->end(), e) == v->end()){
          v->push_back(e);
        }
      };
      // left/right edge
      auto infinite = vector<char>({});
      for( int row=0; row<_size; row++){
        addIfNotAlreadyAdded(&infinite, _field[row][0]);
        addIfNotAlreadyAdded(&infinite, _field[row][_size-1]);
      }
      // top/bottom
      for( int col=0; col<_size; col++) {
          addIfNotAlreadyAdded(&infinite,_field[0][col]);
          addIfNotAlreadyAdded(&infinite, _field[_size-1][col]);
      }
      return infinite;
    }

    int _counter = 0;
    const int _size = 10;
    vector<vector<char>> _field; 
    vector<std::pair<Point, char>> _dest = {};
};

/** @description reads the selected file into a std::vector<string> */
vector<Point> readInputFile(const string fileName){
  auto inputFile = std::ifstream(fileName);
  auto line = string();
  auto returnVector = vector<Point>();

  while( std::getline(inputFile, line)){
    if( line.length() > 0){
      returnVector.push_back(Point(line));
    }
  }
  return returnVector;
};


int64_t solutionPart1(){
  const auto coordinates = readInputFile("input.txt");
  Field field(365);
  auto i = 'a';
  for( auto &p: coordinates ){
    field.addPoint(Point(p), i++);
  }
  field.calcShortestDistance();
  //field.print();
  auto allAreas = field.getAreas();
  auto maxArea =  *std::max_element(allAreas.begin(), allAreas.end());
  return maxArea;
}

int64_t solutionPart2(){

}

int main(){
  auto sol1 = solutionPart1();
  std::cout << "Solution Part 1: " <<  sol1 << "\n";

  auto sol2 = solutionPart2();
  std::cout << "Solution Part 2: " <<  sol2 << "\n";
}

