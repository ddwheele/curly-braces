#ifndef ASTAR_H
#define ASTAR_H

#include <vector>
#include <memory>
#include "PathPlanner.h"
#include "AStarNode.h"
#include <map>
//#include "DrawMapAStar.h"
#include "IDrawMap.h"

using namespace std;

class AStar : public PathPlanner {
public:
	AStar(const vector<shared_ptr<AStarNode>>& nodes,
		const vector<pair<shared_ptr<AStarNode>,shared_ptr<AStarNode>>>& edges, 
		const vector<double>& weights);

	void findPath() override;

	const map<shared_ptr<AStarNode>, vector<pair<shared_ptr<AStarNode>,double>>>& getAdjacencyMatrix() const;

	const shared_ptr<AStarNode>& getGoal() const;

private:
	unique_ptr<IDrawMap> drawMap;

  vector<shared_ptr<AStarNode> > nodes;

  // Adjacency matrix
  map<shared_ptr<AStarNode>, vector<pair<shared_ptr<AStarNode>,double>>> adj;

  shared_ptr<AStarNode> goal;
  shared_ptr<AStarNode> start;
};


#endif