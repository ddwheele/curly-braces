#include <iostream>
#include <algorithm>
#include <limits>
#include "DStarLite.h"

DStarLite::DStarLite(const vector<shared_ptr<DStarNode>>& _nodes,
											const vector<vector<shared_ptr<DStarNode>>>& edges, 
											const vector<double>& weights,
											const shared_ptr<DStarNode>& _start,
											const shared_ptr<DStarNode>& _goal) : nodes(_nodes), start(_start), goal(_goal) {
	if(edges.size() != weights.size()) {
		throw std::invalid_argument("weights and edges must be equal length");
	}
	for(int i=0; i<edges.size(); i++) {
		cout << edges[i][0]->getName() << " to " << edges[i][1]->getName() << " = " << weights[i] << endl;
		cost[edges[i][0]][edges[i][1]] = weights[i];
		cost[edges[i][1]][edges[i][0]] = weights[i];
	}
}

void DStarLite::updateVertex(const std::shared_ptr<DStarNode>& node) {
	cout << "Updating " << *node << endl;
	if(node != goal) {
		// set rhs to minimum of cost through neighbors
		double best = numeric_limits<double>::max();
		for(auto& [ney, cst] : cost[node]) {
			cout<<"\tneighbor = " << ney->getName() << ", cost = " << cst << endl;
			best = std::min(best, cst + ney->getGn());
		}
		cout << "\tsetting to RHS to " << best  << endl;
		node->setRhs(best);
	}
	if(openSet.contains(node)) {
		openSet.deleteNode(node);
	}
	if(!node->gnEqualsRhs()) {
		cout << "\tInconsistent, putting on open set" << endl;
		node->computeKey(key_modifier);
		openSet.insertNode(node);
	}
}

void DStarLite::computeShortestPath() {
	int stepsLeft = maxSteps;
 	while(openSet.getSize() > 0 && 
 	((openSet.peek()->getKey() < start->computeKey(key_modifier)) || (start->getRhs() > start->getGn()) )) {
		if(stepsLeft-- <=0 ) {
			cout << "Did not find a path in " << maxSteps<< " iterations. Aborting." << endl;
			break;
		}
		auto node = openSet.extractMin();
		cout << "Examining " << *node << endl;
		DStarNode::Key oldKey = node->getKey();
		if(node->computeKey(key_modifier) > oldKey ) {
			cout << "\t-key got bigger, put back in openSet" << endl;
			openSet.insertNode(node);
		} else if(node->getGn() > node->getRhs()) {
			cout << "\t-G > RHS, relaxing G and calling the neighbors" << endl;
			// relax g
			node->setGn(node->getRhs());

			// inform predecessors they may have better value now
			for(auto& [ney, _] : cost[node]) {
				updateVertex(ney);
			}
		} else {
			cout << "\t-G <= RHS, blowing up G and calling the neighbors" << endl;
			double oldGn = node->getGn();
			// give up and reset g to inf
			node->setGn(numeric_limits<double>::max());

			// go through predecessors
			for(auto& [ney, _] : cost[node]) {
				updateVertex(ney);
			}
			updateVertex(node);
		}
  }
//	start->setGn(start->getRhs());
	cout << "Shortest path computed in " << (maxSteps - stepsLeft) << " steps." << endl;
}

// must have start and goal nodes defined
// all nodes must have calculated heuristic
// order. Note that, in an actual
// implementation, Initialize() only needs to initialize a vertex
// when it encounters it during the search and thus does not
// need to initialize all v
void DStarLite::initialize() {
	openSet.clear();
	key_modifier = 0;
	for(auto nd : nodes) {
		nd->setRhs(numeric_limits<double>::max());
		nd->setGn(numeric_limits<double>::max());
	}
	goal->setRhs(0);
	goal->computeHeuristic(start);
	goal->computeKey(key_modifier);
	openSet.insertNode(goal);
}

void DStarLite::findPath()  {
	shared_ptr<DStarNode> lastStart = start;
	initialize();
	computeShortestPath();
	while(start != goal) {
		if(Utils::equals(start->getGn(), numeric_limits<double>::max()) {
			cout << "No path found" << endl;
		}
		double best = numeric_limits<double>::max();
		// find the neighbor with lowest g + cost to start
		shared_ptr<DStarNode> nextNode;
		for(auto& [ney, cst] : cost[start]) {
			double est = ney->getGn() + cst;
			if(est < best) {
				best = est;
				nextNode = ney;
			}
			// move to nextNode
			cout << "%%%%%%%%%%%% ADVANCE TO NODE " << nextNode->getName() << "%%%%%%%%%%%%" << endl;

			// did anything change?

			// if anything changed
			// increment km by h(start, lastStart)
			key_modifier += start->distanceTo(*lastStart);
			lastStart = start;
			// for all edge changes
			// update edge cost in cost
			// update vertex
			//compute shortest path
		}
		

	}



}

void DStarLite::printState() const {
	cout << "====================  D*Lite  ====================" << endl;
	for(auto n : nodes) {
		cout << *n << endl;
	}
	cout << "==================================================" << endl;
}

// if a Node has changed
void DStarLite::recalculateNode(shared_ptr<DStarNode>& changed) {
	// key_modifier += changed->computeHeuristic(start);

	// for(auto ney : changed->getDStarNeighbors()) {
	// 	if(ney != start) {
	// 		ney->setRhs(std::min(ney->getRhs(), changed->distanceTo(*ney)+ changed->getGn()));
	// 	}
	// 	updateVertex(ney);
	// }
	// updateVertex(changed);
	// computeShortestPath();
}