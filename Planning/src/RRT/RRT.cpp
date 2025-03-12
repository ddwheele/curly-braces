#include <iostream>
#include <limits>
#include <cmath>
#include <optional>
#include "RRT.h"

using namespace std;


RRT::RRT(shared_ptr<RrtNode> _start, shared_ptr<RrtNode> _goal, const vector<Obstacle>& _obstacles, double _stepSize) 
 : start(std::move(_start)), goal(std::move(_goal)), stepSize(_stepSize), obstacles(_obstacles), drawMap(*this) {
  startTree.push_back(start);
  goalTree.push_back(goal);
}

shared_ptr<RrtNode> RRT::findNearest(const vector<shared_ptr<RrtNode>>& tree, double x, double y) const {
  shared_ptr<RrtNode> ret;
  double closest = std::numeric_limits<double>::max();
  for(const auto& RrtNode : tree) {
    double dist = RrtNode->distanceTo(x, y);
    if(dist < closest) {
      closest = dist;
      ret = RrtNode;
    }
  }
  return ret;
}

bool RRT::hitsAnObstacle(const shared_ptr<RrtNode>& n) {
  for(auto& o : obstacles) {
    if(o.intersects(*n)) {
      return true;
    }
  }
  return false;
}

void RRT::findPath() {
  std::srand(std::time(0));

  bool useStartTree = true;

  for(int i=0; i<Utils::NUM_STEPS; i++) {
    // create random point
    double randX = std::rand() % static_cast<int>(Utils::WIDTH);
    double randY = std::rand() % static_cast<int>(Utils::HEIGHT);

    // find nearest RrtNode from current tree
    shared_ptr<RrtNode> nearest; 
    if(useStartTree) {
      nearest = findNearest(startTree, randX, randY); 
    } else {
      nearest = findNearest(goalTree, randX, randY); 
    }

    // Make new RrtNode and add to tree if they don't intersect obstacle
    shared_ptr<RrtNode> candidateRrtNode = RrtNode::growToward(nearest, randX, randY, stepSize);

    if(hitsAnObstacle(candidateRrtNode)) {

      continue;
    }
    shared_ptr<RrtNode> nearestOther;
    if(useStartTree) {
      startTree.push_back(candidateRrtNode);
      nearestOther = findNearest(goalTree, candidateRrtNode->x, candidateRrtNode->y);
    } else {
      goalTree.push_back(candidateRrtNode);
      nearestOther = findNearest(startTree, candidateRrtNode->x, candidateRrtNode->y);
    }

    if(!nearestOther) {
      candidateRrtNode->printMe();
    }
    double nx = nearestOther->x;
    double ny = nearestOther->y;
    if(candidateRrtNode->distanceTo(nx, ny) < stepSize) {

      linkRrtNode1 = candidateRrtNode;
      linkRrtNode2 = nearestOther;
      cout << i << " steps" << endl;
      drawMap.drawMap();
      drawMap.drawFinalPath();
      return;
    }

    drawMap.drawMap();

    useStartTree = !useStartTree;
  }
  cout << "Ran out of steps! " << Utils::NUM_STEPS << endl;
}


void RRT::printMe() const {
  cout << "Start: ";
  start->printMe();
  cout << "Goal: ";
  goal->printMe();
  for(auto& o : obstacles) {
    o.printMe();
  }
}

const vector<Obstacle>& RRT::getObstacles() const {
  return obstacles;
} 

const RrtNode& RRT::getStart() const {
  return *start;
}

const RrtNode& RRT::getGoal() const {
  return *goal;
}

const shared_ptr<RrtNode>& RRT::getLinkRrtNode1() const {
  return linkRrtNode1;
}

const shared_ptr<RrtNode>& RRT::getLinkRrtNode2() const {
  return linkRrtNode2;
}

const vector<shared_ptr<RrtNode>>& RRT::getStartTree() const {
  return startTree;
}

const vector<shared_ptr<RrtNode>>& RRT::getGoalTree() const {
  return goalTree;
}

