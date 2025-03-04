#ifndef RRT_H
#define RRT_H

#include <memory>
#include <opencv2/opencv.hpp>
#include "RrtNode.h"
#include "Obstacle.h"
#include "Constants.h"
#include "PathPlanner.h"
#include "DrawMapRrt.h"

using namespace std;

class RRT : public PathPlanner {
public:
  RRT(shared_ptr<RrtNode> _start,
    shared_ptr<RrtNode> _goal, 
    const vector<Obstacle> _obstacles,
    double _stepSize=0.2);

  void findPath();
  void printMe() const;
  shared_ptr<RrtNode> findNearest(const vector<shared_ptr<RrtNode>>& tree,
   double x, double y) const;

  vector<Obstacle> getObstacles() const;
  const RrtNode& getStart() const;
  const RrtNode& getGoal() const;

  vector<shared_ptr<RrtNode>> getStartTree() const;
  vector<shared_ptr<RrtNode>> getGoalTree() const;

  // shared ptr because DrawMap needs to iterate through children
   shared_ptr<RrtNode> getLinkRrtNode1() const;
   shared_ptr<RrtNode> getLinkRrtNode2() const;


private:
  DrawMapRrt drawMap;
  shared_ptr<RrtNode> start;
  shared_ptr<RrtNode> goal;
  vector<shared_ptr<RrtNode>> startTree;
  vector<shared_ptr<RrtNode>> goalTree;
  vector<Obstacle> obstacles;
  shared_ptr<RrtNode> linkRrtNode1;
  shared_ptr<RrtNode> linkRrtNode2;
  double stepSize;

  bool hitsAnObstacle(const shared_ptr<RrtNode>& n);
};

#endif