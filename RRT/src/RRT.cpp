#include <iostream>

#include "RRT.h"

using namespace std;


RRT::RRT(shared_ptr<Node> _start, shared_ptr<Node> _goal, vector<Obstacle> _obstacles) 
 :  start(std::move(_start)), goal(std::move(_goal)), obstacles(_obstacles) {
  startTree.push_back(start);
  goalTree.push_back(goal);
}

shared_ptr<Node> RRT::findNearest(const vector<shared_ptr<Node>>& tree, double x, double y) const {
  shared_ptr<Node> ret;
  double closest = Constants::HEIGHT + Constants::WIDTH;
  for(const auto& node : tree) {
    double dist = node->distanceTo(x, y);
    if(dist < closest) {
      closest = dist;
      ret = node;
    }
  }
  return ret;
}

bool RRT::hitsAnObstacle(const shared_ptr<Node>& n) {
  for(auto& o : obstacles) {
    if(o.intersects(*n)) {
      cout << "** HIT AN OBSTACLE - ABORT" << endl;
      return true;
    }
  }
  return false;
}

void RRT::findPath() {
  std::srand(std::time(0));

  bool useStartTree = true;

  for(int i=0; i<Constants::NUM_STEPS; i++) {
    // create random point
    double randX = std::rand() % static_cast<int>(Constants::WIDTH);
    double randY = std::rand() % static_cast<int>(Constants::HEIGHT);

    // find nearest Node from current tree
    shared_ptr<Node> nearest; 
    if(useStartTree) {
      nearest = findNearest(startTree, randX, randY); 
    } else {
      nearest = findNearest(goalTree, randX, randY); 
    }

    // Make new node and add to tree if they don't intersect obstacle
    shared_ptr<Node> candidateNode = Node::growToward(nearest, randX, randY);

    cout << "candidateNode = ";
    candidateNode->printMe();

    if(hitsAnObstacle(candidateNode)) {
      continue;
    }
    
    shared_ptr<Node> nearestOther;
    if(useStartTree) {
      startTree.push_back(candidateNode);
      nearestOther = findNearest(goalTree, candidateNode->x, candidateNode->y);
    } else {
      goalTree.push_back(candidateNode);
      nearestOther = findNearest(startTree, candidateNode->x, candidateNode->y);
    }

    if(candidateNode->distanceTo(*nearestOther) < Constants::STEP_SIZE) {
      linkNode1 = candidateNode;
      linkNode2 = nearestOther;
      drawTree();
      drawFinalPath();
      cout <<"Goodnight and thank you" << endl;
      return;
    }

    drawTree();

    useStartTree = !useStartTree;
  }
}

void RRT::drawFinalPath() {
  shared_ptr<Node> curr = linkNode1;
  while(curr && curr->parent) {
    drawNode(curr, Constants::BLUE, 2);
    curr = curr->parent;
  }
  curr = linkNode2;
  while(curr && curr->parent) {
    drawNode(curr, Constants::BLUE, 2);
    curr = curr->parent;
  }
  cv::imshow("Tree", mat);
  cv::waitKey(0);
} 

void RRT::drawTree() {
  mat = cv::Mat(Constants::HEIGHT_PX, Constants::WIDTH_PX, CV_8UC3, Constants::WHITE);
  for(auto& o : obstacles) {
    drawObstacle(o);
  }
  drawEndpoint(start, Constants::GREEN);
  drawEndpoint(goal, Constants::RED);

  for(auto nd : startTree) {
    if (nd->parent) {
      drawNode(nd, Constants::BLACK);
    }
  }

  for(auto nd : goalTree) {
    if (nd->parent) {
      drawNode(nd, Constants::BLACK);
    }
  }

  cv::imshow("Tree", mat);
  cv::waitKey(1000);
}

void RRT::drawNode(const shared_ptr<Node>& n, const cv::Scalar& color, int width) const {
  cv::line(mat, n->getCvPoint(), 
                n->parent->getCvPoint(),
                color, width);
}

void RRT::drawEndpoint(const shared_ptr<Node>& n, const cv::Scalar& color) const {
  cv::circle(mat, n->getCvPoint(), Constants::RADIUS_PX, color, -1);
}

void RRT::drawObstacle(const Obstacle& o) const {
  cv::rectangle(mat, o.getMinCvPoint(), o.getMaxCvPoint(), Constants::GRAY, -1);
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

