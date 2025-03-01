#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <opencv2/opencv.hpp>

struct Constants {
  static constexpr int SCALE = 50; // conversion from units to pixels for drawing

  static constexpr double HEIGHT = 10.0; // size of canvas in units
  static constexpr double WIDTH = 10.0; // size of canvas in units
  static constexpr double STEP_SIZE = 0.1; // for building tree

  static constexpr int HEIGHT_PX = HEIGHT * SCALE; // size of canvas in pixels
  static constexpr int WIDTH_PX = WIDTH * SCALE; // size of canvas in pixels

  static constexpr int RADIUS_PX = 15; // for drawing Nodes


	static inline cv::Scalar WHITE = cv::Scalar(255, 255, 255);
	static inline cv::Scalar BLACK = cv::Scalar(0, 0, 0);
	static inline cv::Scalar RED = cv::Scalar(0, 0, 255);
	static inline cv::Scalar GREEN = cv::Scalar(0, 255, 0);
	static inline cv::Scalar BLUE = cv::Scalar(255, 0, 0);
	static inline cv::Scalar GRAY = cv::Scalar(100, 100, 100);

};


#endif