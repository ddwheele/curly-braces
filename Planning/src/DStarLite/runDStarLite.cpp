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
 
void addEdge(vector<vector<shared_ptr<DStarNode>>>& edges, vector<double>& weights, shared_ptr<DStarNode>& a, shared_ptr<DStarNode>& b, double w) {
  edges.push_back({a,b});
  weights.push_back(w);
  a->addDStarNeighbor(b);
  b->addDStarNeighbor(a);
}

DStarLite createDStarLite() {
  // create nodes
  vector<shared_ptr<DStarNode>> nodes;
  shared_ptr<DStarNode> a = make_shared<DStarNode>("A", 1, 10);
  shared_ptr<DStarNode> b = make_shared<DStarNode>("B", 7, 10);
  shared_ptr<DStarNode> c = make_shared<DStarNode>("C", 12, 7);
  shared_ptr<DStarNode> d = make_shared<DStarNode>("D", 12, 12);
  shared_ptr<DStarNode> g = make_shared<DStarNode>("G", 18, 10);

  nodes.push_back(a);
  nodes.push_back(b);
  nodes.push_back(c);
  nodes.push_back(d);
  nodes.push_back(g);
 
  // create edges
  vector<vector<shared_ptr<DStarNode>>> edges;
  vector<double> weights;
  
  addEdge(edges, weights, a, b, 10);
  addEdge(edges, weights, b, c, 10);
  addEdge(edges, weights, c, g, 10);
  addEdge(edges, weights, b, d, 10);
  addEdge(edges, weights, d, g, 100);

  vector<shared_ptr<DStarNode>> obs = {c, b, a};

  DStarLite dsl(nodes, edges, weights, a, g);
  dsl.setTimedObstacles(obs);

  return dsl;
 }
 
int main(int argc, char** argv) {
  DStarLite dsl = createDStarLite();
  dsl.findPath();
  return 0;
}











