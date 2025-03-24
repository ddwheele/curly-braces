#include <iostream>
#include <limits>
#include <cmath>
#include <optional>
#include "RRT.h"

using namespace std;


RRT::RRT(const shared_ptr<RrtNode>& _start, const shared_ptr<RrtNode>& _goal, const vector<Obstacle>& _obstacles, double _stepSize) 
 : start(std::move(_start)), goal(std::move(_goal)), obstacles(std::move(_obstacles)), stepSize(_stepSize), drawMap(*this) {
  startTree.push_back(start);
  goalTree.push_back(goal);
}

// return the nearest node in the tree to the given point
shared_ptr<RrtNode> RRT::findNearest(const vector<shared_ptr<RrtNode>>& tree, const double x, const double y) const {
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

    // Make new RrtNode as child of closest node, in the direction of that point 
    shared_ptr<RrtNode> candidateRrtNode = RrtNode::growToward(nearest, randX, randY, stepSize);

    if(hitsAnObstacle(candidateRrtNode)) {
      continue;
    }
    // add new node to current tree if it doesn't intersect obstacle
    // find the nearest node in the other tree
    shared_ptr<RrtNode> nearestOther;
    if(useStartTree) {
      startTree.push_back(candidateRrtNode);
      nearestOther = findNearest(goalTree, candidateRrtNode->x, candidateRrtNode->y);
    } else {
      goalTree.push_back(candidateRrtNode);
      nearestOther = findNearest(startTree, candidateRrtNode->x, candidateRrtNode->y);
    }

    if(!nearestOther) {
      // shouldn't happen, there should always be a nearestOther
      candidateRrtNode->printMe();
    }

    double nx = nearestOther->x;
    double ny = nearestOther->y;
    
    // check if the nearest node in the other tree is close enough to current tree
    if(candidateRrtNode->distanceTo(nx, ny) < stepSize) {
      
      // join the trees if no obstacles in the way
      shared_ptr<RrtNode> linker = make_shared<RrtNode>(candidateRrtNode->x, candidateRrtNode->y, nearestOther);

      // verify linker does not hit an obstacle
      if(!hitsAnObstacle(linker)) {
        linkRrtNode1 = candidateRrtNode;
        linkRrtNode2 = nearestOther;
        cout << i << " steps" << endl;
        drawMap.drawFinalPath();
        return;
      }
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

