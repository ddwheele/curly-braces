#ifndef ASTAR_H
#define ASTAR_H

#include <vector>
#include <memory>
#include "PathPlanner.h"
#include "AStarNode.h"
#include "DrawMapAStar.h"

class AStar : public PathPlanner {
public:
	AStar(vector<shared_ptr<AStarNode>> nodes,
		vector<pair<shared_ptr<AStarNode>,shared_ptr<AStarNode>>> edges, 
		vector<double> weights);

	void findPath();

	map<shared_ptr<AStarNode>, vector<pair<shared_ptr<AStarNode>,double>>> getAdjacencyMatrix() const;

private:
	DrawMapAStar drawMap;

  vector<shared_ptr<AStarNode> > nodes;

  // Adjacency matrix
  map<shared_ptr<AStarNode>, vector<pair<shared_ptr<AStarNode>,double>>> adj;

  shared_ptr<AStarNode> goal;
  shared_ptr<AStarNode> start;
};


#endif