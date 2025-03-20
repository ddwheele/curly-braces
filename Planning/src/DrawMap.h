#ifndef DRAW_MAP_H
#define DRAW_MAP_H

#include <memory>
#include <opencv2/opencv.hpp>
#include "IDrawMap.h"
#include "Utils.h"
#include "Node.h"

class PathPlanner;

class DrawMap : public IDrawMap {
public:

	// is the point within the drawing canvas?
  static bool isInBounds(const double x, const double y) {
		if(x >=0 && x <= Utils::WIDTH && y>=0 && y <= Utils::HEIGHT) {
			return true;
		}
		return false;
	}

  static cv::Point getCvPoint(const Node& node);

protected:
  cv::Mat mat;
 
  // used by DrawMapRrt
  void drawColoredNode(const Node& n, 
 		const cv::Scalar& color) const;

  static constexpr int RADIUS_PX = 25; // for drawing Node

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