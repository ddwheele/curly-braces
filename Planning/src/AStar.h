#ifndef ASTAR_H
#define ASTAR_H

#include <vector>
#include <memory>
#include "PathPlanner.h"
#include "AStarNode.h"

class AStar : public PathPlanner {
public:
	AStar(vector<shared_ptr<AStarNode>> nodes,
		vector<pair<shared_ptr<AStarNode>,shared_ptr<AStarNode>>> edges, 
		vector<double> weights);

	void findPath();

	map<shared_ptr<AStarNode>, vector<pair<shared_ptr<AStarNode>,double>>> getAdjacencyMatrix() const;

	vector<shared_ptr<AStarNode>> getNodes() const;

	int getA() const;

private:
  vector<shared_ptr<AStarNode> > nodes;

  int a = 1;

  // Adjacency matrix
  map<shared_ptr<AStarNode>, vector<pair<shared_ptr<AStarNode>,double>>> adj;

  shared_ptr<AStarNode> goal;
  shared_ptr<AStarNode> start;
};


#endif