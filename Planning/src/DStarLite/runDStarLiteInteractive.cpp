#include <iostream>
#include <unordered_set>

#include "DStarLite.h"
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

DStarLite createDStarLiteAll() {
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

  DStarLite dsl(longRow, edges, weights, start, goal);

  return dsl;
}

// wanted is subset of lettered nodes from the chart above, goalchar can be a wanted node or 
DStarLite createDStarLite(const unordered_set<char>& wanted, string goalchar) {
  shared_ptr<DStarNode> goal ;
  // create nodes
  int ROW_LEN = 5;
  double U = 2.5;
  double offset = 5;
  bool goalNodeWasLetter = false;
  vector<vector<optional<shared_ptr<DStarNode>>>> nodes;
  for(int r=0; r<ROW_LEN; r++) {
    vector<optional<shared_ptr<DStarNode>>> row;
    for(int c=0; c<ROW_LEN; c++) {
      char label = 'A'+c+(r*ROW_LEN);
      if(wanted.count(label)) {
        row.push_back( make_shared<DStarNode>(label, c*U+offset, r*U+ offset) );
        if(goalchar.size() == 1 && label==goalchar[0]) {
          goal = row.back().value();
          goalNodeWasLetter = true;
        }
      } else {
        row.push_back({});
      }
    }
    nodes.push_back(row);
  }

  shared_ptr<DStarNode> start = make_shared<DStarNode>("Start", 2, 10);
  if(!goalNodeWasLetter) {
    goal = make_shared<DStarNode>("Goal", 18, 10);
  }
  // create edges
  vector<vector<shared_ptr<DStarNode>>> edges;
  vector<double> weights;
  
  for(int row=0; row<ROW_LEN; row++) {
    if(nodes[row][0].has_value()) {
      addEdge(edges, weights, start, nodes[row][0].value(), start->distanceTo(*nodes[row][0].value()));
    }
    if(nodes[row][ROW_LEN-1].has_value()) {
      addEdge(edges, weights, nodes[row][ROW_LEN-1].value(), goal, goal->distanceTo(*nodes[row][ROW_LEN-1].value()));
    }
    for(int col=1; col<ROW_LEN; col++) {
      if(nodes[row][col-1].has_value() && nodes[row][col].has_value()) {
        addEdge(edges, weights, nodes[row][col-1].value(), nodes[row][col].value(), nodes[row][col-1].value()->distanceTo(*nodes[row][col].value()));
      }
      
      if(row-1 >=0) {
        for(int neigh=1; neigh<ROW_LEN; neigh++) {
          if(nodes[row-1][col-1].has_value() && nodes[row][col].has_value()) {
            addEdge(edges, weights, nodes[row-1][col-1].value(), nodes[row][col].value(), nodes[row-1][col-1].value()->distanceTo(*nodes[row][col].value()));
          }
          if(nodes[row][col-1].has_value() && nodes[row-1][col].has_value()) {
            addEdge(edges, weights, nodes[row][col-1].value(), nodes[row-1][col].value(), nodes[row][col-1].value()->distanceTo(*nodes[row-1][col].value()));
          }
        }
      }
    }
  }

  vector<shared_ptr<DStarNode>> longRow;

  for(auto rw : nodes) {
    for(auto n: rw) {
      if(n.has_value()) {
        longRow.push_back(n.value());
      }
    }
  }
  longRow.push_back(start);
  if(!goalNodeWasLetter) {
     longRow.push_back(goal);
  }

  cout << "edges = " << edges.size() << endl;

  DStarLite dsl(longRow, edges, weights, start, goal);

  return dsl;
 }

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
int main(int argc, char** argv) {
 // cout << " Start" << endl;
  DStarLite dsl = createDStarLiteAll();
  // unordered_set<char> nodes = {
  //   'G',
  // 'K','L','M',
  // 'P','Q','R','S'};
  // DStarLite dsl = createDStarLite(nodes, "S");

  dsl.findPathInteractive();
  
  return 0;
}

