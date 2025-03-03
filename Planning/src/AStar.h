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


private:
	cv::Mat mat;
  vector<shared_ptr<AStarNode> > nodes;
  map<shared_ptr<AStarNode>, vector<pair<shared_ptr<AStarNode>,double> > > adj;
  shared_ptr<AStarNode> goal;
  shared_ptr<AStarNode> start;
};


#endif