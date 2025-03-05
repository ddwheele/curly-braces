#include <cmath>
#include <iostream>
#include <fstream>
#include <ranges>
#include <yaml-cpp/yaml.h>
#include <opencv2/opencv.hpp>
#include <cstdlib>
#include <ctime>
#include <memory>

#include "AStarRandom.h"
#include "StarNode.h"
#include "Utils.h"

using namespace std;
 
vector<shared_ptr<StarNode>> createNodes(int numNodes) {
  // create nodes
  vector<shared_ptr<StarNode>> nodes;
  shared_ptr<StarNode> start = make_shared<StarNode>("Start", 1,1);
  shared_ptr<StarNode> goal = make_shared<StarNode>("Goal", Utils::WIDTH-1,Utils::HEIGHT-1);

  for(int i=0; i<numNodes; i++) {
    nodes.push_back(make_shared<StarNode>(string(1, 'A' + i)));
  }

  // every node needs some neighbors
  int REQUIRED_NEIGHBORS = 2;
  std::srand(std::time(0));

  //   bool added = nd->addNeighbor(nodes[index]);
  // for(auto nd : nodes) {
  //   cout <<"Node ";
  //   nd->printMe();
  //   cout <<"\t has these neighbors" << endl;
  
  //  }

  //  start->addNeighbor(nodes[0]);
  //  goal->addNeighbor(nodes[numNodes-1]);

  // nodes.push_back(start);
  // nodes.push_back(goal);


   return nodes;
 }
 
int main(int argc, char** argv) {
  vector<shared_ptr<StarNode>> nodes = createNodes(6);
  AStarRandom aStarRandom(nodes);
  aStarRandom.findPath();
  return 0;
}











