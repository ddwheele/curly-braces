#include <iostream>
#include <unordered_set>

#include "DStarLiteOptimized.h"
#include "DStarNode.h"
#include "StarNode.h"
#include "Utils.h"

using namespace std;

void addEdge(vector<vector<shared_ptr<DStarNode>>>& edges, vector<double>& weights, shared_ptr<DStarNode>& a, shared_ptr<DStarNode>& b, double w) {
  edges.push_back({a,b});
  weights.push_back(w);
  a->addDStarNeighbor(b);
  b->addDStarNeighbor(a);
}

DStarLiteOptimized createDStarLiteOptimized() {
  // create nodes
  int ROW_LEN = 5;
  double U = 2.5;
  double offset = 5;
  vector<vector<shared_ptr<DStarNode>>> nodes;
  for(int r=0; r<ROW_LEN; r++) {
    vector<shared_ptr<DStarNode>> row;
    for(int c=0; c<ROW_LEN; c++) {
      row.push_back( make_shared<DStarNode>('A'+c+(r*ROW_LEN), c*U+offset, r*U+ offset) );
    }
    nodes.push_back(row);
  }

  shared_ptr<DStarNode> start = make_shared<DStarNode>("Start", 2, 10);
  shared_ptr<DStarNode> goal = make_shared<DStarNode>("Goal", 18, 10);
 
  // create edges
  vector<vector<shared_ptr<DStarNode>>> edges;
  vector<double> weights;
  
  for(int row=0; row<ROW_LEN; row++) {
    addEdge(edges, weights, start, nodes[row][0], start->distanceTo(*nodes[row][0]));
    addEdge(edges, weights, nodes[row][ROW_LEN-1], goal, goal->distanceTo(*nodes[row][ROW_LEN-1]));

    for(int col=1; col<ROW_LEN; col++) {
      addEdge(edges, weights, nodes[row][col-1], nodes[row][col], nodes[row][col-1]->distanceTo(*nodes[row][col]));
      if(row-1 >=0) {
        for(int neigh=1; neigh<ROW_LEN; neigh++) {
          addEdge(edges, weights, nodes[row-1][col-1], nodes[row][col], nodes[row-1][col-1]->distanceTo(*nodes[row][col]));
          addEdge(edges, weights, nodes[row][col-1], nodes[row-1][col], nodes[row][col-1]->distanceTo(*nodes[row-1][col]));
        }
      }
    }
  }

  vector<shared_ptr<DStarNode>> longRow;
  longRow.reserve(ROW_LEN*ROW_LEN);

  for(auto rw : nodes) {
    longRow.insert(longRow.end(), rw.begin(), rw.end());
  }
  longRow.push_back(start);
  longRow.push_back(goal);

  DStarLiteOptimized dsl(longRow, edges, weights, start, goal);
  return dsl;
}

int main(int argc, char** argv) {
  DStarLiteOptimized dsl = createDStarLiteOptimized();
  cout << "Calling DSLO findPath()" << endl;
  dsl.findPath();
  dsl.drawMapAndWait();
  return 0;
}
