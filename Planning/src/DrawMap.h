#ifndef DRAW_MAP_H
#define DRAW_MAP_H

#include <memory>
#include <opencv2/opencv.hpp>
#include "RrtNode.h"
#include "Obstacle.h"
#include "Constants.h"

class PathPlanner;

class DrawMap {
public:
	DrawMap(const PathPlanner& _planner);
	void drawRrtTree();
  void drawFinalRrtPath();

private:
  cv::Mat mat;
  const PathPlanner& planner;  // Reference to the RRT object (read-only)
 
  void drawObstacle(const Obstacle& o) const;
  void drawColoredNode(const Node& n, 
 		const cv::Scalar& color) const;

  void drawRrtNode(const RrtNode& n,
  	const cv::Scalar& color, int width=1) const;
};

#endif