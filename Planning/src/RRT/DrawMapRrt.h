#ifndef DRAW_MAP_RRT_H
#define DRAW_MAP_RRT_H

#include <memory>
#include <opencv2/opencv.hpp>
#include "RrtNode.h"
#include "Obstacle.h"
#include "DrawMap.h"

class RRT;

class DrawMapRrt : public DrawMap {
public:
	DrawMapRrt(const RRT& _rrt);

  void drawMap() override;
  void drawFinalPath() override;

private:
  const RRT& rrt; 
  void drawRrtNode(const RrtNode& n,
  	const cv::Scalar& color, const int width=1) const;

  void drawObstacle(const Obstacle& o) const;
};

#endif