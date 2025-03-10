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
  int ROW_LEN = 5;
  double U = 2.5;
  double offset = 5;
  cout << "Creating nodes " << endl;
  vector<vector<shared_ptr<DStarNode>>> nodes;
  for(int r=0; r<ROW_LEN; r++) {
    vector<shared_ptr<DStarNode>> row;
    for(int c=0; c<ROW_LEN; c++) {
      row.push_back( make_shared<DStarNode>('A'+c+(r*ROW_LEN), c*U+offset, r*U+ offset) );
    }
    nodes.push_back(row);
  }

  cout << "nodes = "<< nodes.size() << ", " << nodes[0].size() << endl;

  shared_ptr<DStarNode> start = make_shared<DStarNode>("Start", 2, 10);
  shared_ptr<DStarNode> goal = make_shared<DStarNode>("Goal", 18, 10);
 
  // // create edges
  vector<vector<shared_ptr<DStarNode>>> edges;
  vector<double> weights;
  
  for(int row=0; row<ROW_LEN; row++) {
    addEdge(edges, weights, start, nodes[row][0], 10);
    addEdge(edges, weights, nodes[row][ROW_LEN-1], goal, 10);

    for(int col=1; col<ROW_LEN; col++) {
      addEdge(edges, weights, nodes[row][col-1], nodes[row][col], 10);
      if(row-1 >=0) {
        for(int neigh=1; neigh<ROW_LEN; neigh++) {
          addEdge(edges, weights, nodes[row-1][col-1], nodes[row][col], 10);
          addEdge(edges, weights, nodes[row][col-1], nodes[row-1][col], 10);
        }

      }

    }
  }

  vector<shared_ptr<DStarNode>> longRow;
  longRow.reserve(ROW_LEN*ROW_LEN);

  cout << "created longRow" << endl;
  for(auto rw : nodes) {
    longRow.insert(longRow.end(), rw.begin(), rw.end());
  }
  longRow.push_back(start);
  longRow.push_back(goal);
  cout << "longRow.size() = " << longRow.size() << endl;
  cout << "edges = " << edges.size() << endl;

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

