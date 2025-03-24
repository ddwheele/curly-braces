#ifndef RRT_H
#define RRT_H

#include <memory>
#include <opencv2/opencv.hpp>
#include "RrtNode.h"
#include "Obstacle.h"
#include "Utils.h"
#include "PathPlanner.h"
#include "DrawMapRrt.h"

using namespace std;

/**
 * Uses RRT to find a path from start to goal that avoids obstacles
 */
class RRT : public PathPlanner {
public:
  // construct with start node, goal node, list of obstacles, and optional size of steps to grow tree
  RRT(const shared_ptr<RrtNode>& _start,
    const shared_ptr<RrtNode>& _goal, 
    const vector<Obstacle>& _obstacles,
    double _stepSize=0.2);

  // use RRT to find a path from start to goal, avoiding obstacles, and display as image
  void findPath() override;
  void printMe() const;
  // find the node in the given tree that is closest to the given x,y 
  shared_ptr<RrtNode> findNearest(const vector<shared_ptr<RrtNode>>& tree,
    const double x, const double y) const;

  const vector<Obstacle>& getObstacles() const;
  const RrtNode& getStart() const;
  const RrtNode& getGoal() const;

  const vector<shared_ptr<RrtNode>>& getStartTree() const;
  const vector<shared_ptr<RrtNode>>& getGoalTree() const;

  // shared ptr because DrawMap needs to iterate through children
  const shared_ptr<RrtNode>& getLinkRrtNode1() const;
  const shared_ptr<RrtNode>& getLinkRrtNode2() const;


private:
  DrawMapRrt drawMap;
  shared_ptr<RrtNode> start;
  shared_ptr<RrtNode> goal;
  vector<shared_ptr<RrtNode>> startTree;
  vector<shared_ptr<RrtNode>> goalTree;
  vector<Obstacle> obstacles;
  // linkRrtNodes are the Nodes in each tree that are close enough to join
  shared_ptr<RrtNode> linkRrtNode1;
  shared_ptr<RrtNode> linkRrtNode2;
  double stepSize;

  bool hitsAnObstacle(const shared_ptr<RrtNode>& n);
};

#endif