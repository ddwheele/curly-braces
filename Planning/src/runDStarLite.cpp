#include <cmath>
#include <iostream>
#include <fstream>
#include <ranges>

#include <cstdlib>
#include <ctime>
#include <memory>

#include "DStarLite.h"
#include "StarNode.h"
#include "Utils.h"

using namespace std;

// clang++ -std=c++20 runDStarLite.cpp DStarNode.cpp DStarLite.cpp StarNode.cpp Node.cpp -o runDStarLite
 
vector<shared_ptr<DStarNode>> createNodes(int num) {
  // create nodes
  vector<shared_ptr<DStarNode>> nodes;
  shared_ptr<DStarNode> start = make_shared<DStarNode>("Start", 1,1);
  shared_ptr<DStarNode> goal = make_shared<DStarNode>("Goal", Utils::WIDTH-1,Utils::HEIGHT-1);
  nodes.push_back(start);
  nodes.push_back(goal);

  for(int i=0; i<num; i++) {
    nodes.push_back(make_shared<DStarNode>(string(1, 'A' + num)));
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
   return nodes;
 }
 
int main(int argc, char** argv) {
  vector<shared_ptr<DStarNode>> nodes = createNodes(10);
  DStarLite dStarLite(nodes);
  return 0;
}











