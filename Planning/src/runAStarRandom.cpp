#include <cmath>
#include <iostream>
#include <fstream>
#include <ranges>
#include <yaml-cpp/yaml.h>
#include <opencv2/opencv.hpp>
#include <cstdlib>
#include <ctime>

#include "AStar.h"
#include "StarNode.h"
#include "Utils.h"

using namespace std;
 
vector<shared_ptr<StarNode>> createGraph(int num) {
  // create nodes
  vector<shared_ptr<StarNode>> nodes;
  shared_ptr<StarNode> start = make_shared("Start", 1,1);
  shared_ptr<StarNode> goal = make_shared("Goal", Utils::WIDTH-1,Utils::HEIGHT-1);
  nodes.push_back(start);
  nodes.push_back(goal);

  for(int i=0; i<num; i++) {
    nodes.push_back(make_shared(string(1, 'A' + num)));
  }

  // every node needs some neighbors
  int REQUIRED_NEIGHBORS = 3;
  std::srand(std::time(0));
  for(auto nd : nodes) {
    int neigh = REQUIRED_NEIGHBORS;
    while(neigh) {
      int index = std::rand() % (num+2);
      bool added = nd->addNeighbor(nodes[index]);
      if(added) {
        neigh--;
      }
    }
   }
 }
 
int main(int argc, char** argv) {
  
       shared_ptr<AStarNode> AStar::getGoal() const {
               return goal;
       }
 
  AStar astar = loadYamlToAStar(params_file);
  astar.findPath();
       return 0;
}











