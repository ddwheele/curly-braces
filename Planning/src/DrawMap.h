#ifndef DRAW_MAP_H
#define DRAW_MAP_H

#include <memory>
#include <opencv2/opencv.hpp>
#include "Obstacle.h"
#include "Constants.h"

class PathPlanner;

class DrawMap {
public:
	virtual void drawMap() = 0;
	virtual void drawFinalPath() = 0;
	virtual ~DrawMap() = default;

protected:
  cv::Mat mat;
 
  void drawObstacle(const Obstacle& o) const;
  void drawColoredNode(const Node& n, 
 		const cv::Scalar& color) const;

  static constexpr int FONT_FACE = cv::FONT_HERSHEY_SIMPLEX;
  static constexpr int FILL_SHAPE = -1;
  static constexpr double FONT_SCALE = 0.5;
  static constexpr double FONT_THICKNESS = 1;

  static inline cv::Point NODE_LABEL_OFFSET = cv::Point(0,0);

};

#endif