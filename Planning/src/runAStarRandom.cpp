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

  // every node connects to its 2 nearest neighbors
  int REQUIRED_NEIGHBORS = 2;
  for(auto nd : nodes) {
    cout <<"Node ";
    nd->printMe();
    cout <<"\t has these neighbors" << endl;
    nd->orderNeighbors(nodes);
    for(int i=0; i<REQUIRED_NEIGHBORS; i++) {
      // index 0 will be itself
      cout << "\t - ";
      nodes[i+1]->printMe();
      nd->addNeighbor(nodes[i+1]);
      nodes[i+1]->addNeighbor(nd);
    }
  }

  start->printMe();
  cout <<"\t has these neighbors" << endl;
  start->orderNeighbors(nodes);
  for(int i=0; i<REQUIRED_NEIGHBORS; i++) {
      // index 0 will be itself
      cout << "\t - ";
      nodes[i+1]->printMe();
      start->addNeighbor(nodes[i+1]);
      nodes[i+1]->addNeighbor(start);
    }

  goal->orderNeighbors(nodes);
  goal->printMe();
  cout <<"\t has these neighbors" << endl;
  goal->orderNeighbors(nodes);
  for(int i=0; i<REQUIRED_NEIGHBORS; i++) {
      // index 0 will be itself
      cout << "\t - ";
      nodes[i+1]->printMe();
      goal->addNeighbor(nodes[i+1]);
      nodes[i+1]->addNeighbor(goal);
    }

  nodes.push_back(start);
  nodes.push_back(goal);

  return nodes;
 }
 
int main(int argc, char** argv) {
  vector<shared_ptr<StarNode>> nodes = createNodes(6);
  AStarRandom aStarRandom(nodes);
  aStarRandom.findPath();
  return 0;
}











