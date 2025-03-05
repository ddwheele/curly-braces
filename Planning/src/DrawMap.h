#ifndef DRAW_MAP_H
#define DRAW_MAP_H

#include <memory>
#include <opencv2/opencv.hpp>
#include "Obstacle.h"
#include "Utils.h"

class PathPlanner;

class DrawMap {
public:
	virtual void drawMap() = 0;
	virtual void drawFinalPath() = 0;
	virtual ~DrawMap() = default;

  static bool isInBounds(const double x, const double y) {
		if(x >=0 && x <= Utils::WIDTH && y>=0 && y <= Utils::HEIGHT) {
			return true;
		}
		return false;
	}

  static cv::Point getCvPoint();

protected:
  cv::Mat mat;
 
  void drawObstacle(const Obstacle& o) const;
  void drawColoredNode(const Node& n, 
 		const cv::Scalar& color) const;

  static constexpr int RADIUS_PX = 15; // for drawing Node

  static inline cv::Scalar WHITE = cv::Scalar(255, 255, 255);
	static inline cv::Scalar BLACK = cv::Scalar(0, 0, 0);
	static inline cv::Scalar RED = cv::Scalar(0, 0, 255);
	static inline cv::Scalar GREEN = cv::Scalar(0, 255, 0);
	static inline cv::Scalar BLUE = cv::Scalar(255, 0, 0);
	static inline cv::Scalar GRAY = cv::Scalar(100, 100, 100);
	static inline cv::Scalar LT_GRAY = cv::Scalar(200, 200, 200);

  static constexpr int HEIGHT_PX = Utils::HEIGHT * Utils::SCALE; // size of canvas in pixels
  static constexpr int WIDTH_PX = Utils::WIDTH * Utils::SCALE; // size of canvas in pixels

  static constexpr int SHOW_DELAY = 10; // in ms
};

#endif