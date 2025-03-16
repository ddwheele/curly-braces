#include <iostream>
#include <algorithm>
#include <limits>
#include "DStarLiteOptimized.h"
#include "DrawMapDStarLite.h"

DStarLiteOptimized::DStarLiteOptimized(const vector<shared_ptr<DStarNode>>& _nodes,
											const vector<vector<shared_ptr<DStarNode>>>& edges, 
											const vector<double>& weights,
											const shared_ptr<DStarNode>& _start,
											const shared_ptr<DStarNode>& _goal) 
											: AbstractDStarLite(_nodes, edges, weights, _start, _goal) {
}



void DStarLiteOptimized::updateVertex(const std::shared_ptr<DStarNode>& node) {
	
}

void DStarLiteOptimized::computeShortestPath() {

}

// must have start and goal nodes defined
// all nodes must have calculated heuristic
void DStarLiteOptimized::initialize() {

}



void DStarLiteOptimized::findPathInteractive()  {
	
}

void DStarLiteOptimized::findPath()  {
  cout << "DStarLiteOptimized::findPath() not implemented. Please use DStarLiteOptimized::findPathInteractive()" << endl;
}

