#include <iostream>

#include "DStarLite.h"
#include "DStarNode.h"
#include "StarNode.h"
#include "Utils.h"

using namespace std;

/*
* Graph:
* 
*     /---- A - B - C - D - E ---\
*    /        X   X   X   X       \
*   /  /--- F - G - H - I - J ---\ \
*  /  /       X   X   X   X       \ \
* Start --- K - L - M - N - O ---- Goal
*  \  \       X   X   X   X       / /
*   \  \--- P - Q - R - S - T ---/ /
*    \        X   X   X   X       /
*     \---- U - V - W - X - Y ---/
*
*/

void addEdge(vector<vector<shared_ptr<DStarNode>>>& edges, vector<double>& weights, shared_ptr<DStarNode>& a, shared_ptr<DStarNode>& b, double w) {
  edges.push_back({a,b});
  weights.push_back(w);
  a->addDStarNeighbor(b);
  b->addDStarNeighbor(a);
}

DStarLite createDStarLite() {
  // create nodes
  int SIZE = 5;
  double U = 2.5;
  double offset = 5;
  cout << "Creating nodes " << endl;
  vector<vector<shared_ptr<DStarNode>>> nodes;
  for(int r=0; r<SIZE; r++) {
    vector<shared_ptr<DStarNode>> row;
    for(int c=0; c<SIZE; c++) {
      row.push_back( make_shared<DStarNode>('A'+c+(r*SIZE), c*U+offset, r*U+ offset) );
    }
    nodes.push_back(row);
  }

  cout << "nodes = "<< nodes.size() << ", " << nodes[0].size() << endl;

  shared_ptr<DStarNode> start = make_shared<DStarNode>("Start", 2, 10);
  shared_ptr<DStarNode> goal = make_shared<DStarNode>("Goal", 18, 10);
 
  // // create edges
   vector<vector<shared_ptr<DStarNode>>> edges;
   vector<double> weights;
  
  // addEdge(edges, weights, a, b, 10);
  // addEdge(edges, weights, b, c, 10);
  // addEdge(edges, weights, c, g, 10);
  // addEdge(edges, weights, b, d, 10);
  // addEdge(edges, weights, d, g, 100);

  vector<shared_ptr<DStarNode>> longRow;
  longRow.reserve(SIZE*SIZE);

  cout << "created longRow" << endl;
  for(auto rw : nodes) {
    longRow.insert(longRow.end(), rw.begin(), rw.end());
  }
  longRow.push_back(start);
  longRow.push_back(goal);
  cout << "longRow.size() = " << longRow.size() << endl;

  DStarLite dsl(longRow, edges, weights, start, goal);

  return dsl;
 }



int main(int argc, char** argv) {
  cout << " Start" << endl;
  DStarLite dsl = createDStarLite();
  cout << "Finished Creating DStar Lite" << endl;
  //dsl.findPath();
  dsl.drawMap();
  return 0;
}

