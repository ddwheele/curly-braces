#ifndef ASTAR_RANDOM_H
#define ASTAR_RANDOM_H

#include <vector>
#include <memory>
#include "PathPlanner.h"
#include "StarNode.h"
#include "DrawMapAStarRandom.h"

class AStarRandom : public PathPlanner {
public:
	AStarRandom(vector<shared_ptr<StarNode>> nodes);

	void findPath();

	map<shared_ptr<StarNode>, vector<pair<shared_ptr<StarNode>,double>>> getAdjacencyMatrix() const;

	shared_ptr<StarNode> getGoal() const;

private:
	DrawMapAStarRandom drawMap;

  vector<shared_ptr<StarNode> > nodes;

  // Adjacency matrix
  map<shared_ptr<StarNode>, vector<pair<shared_ptr<StarNode>,double>>> adj;

  shared_ptr<StarNode> goal;
  shared_ptr<StarNode> start;
};


#endif