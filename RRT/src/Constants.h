#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <opencv2/opencv.hpp>

struct Constants {
  static constexpr int SCALE = 50; // conversion from units to pixels for drawing

  static constexpr double HEIGHT = 10.0; // size of canvas in units
  static constexpr double WIDTH = 10.0; // size of canvas in units

  static constexpr int HEIGHT_PX = HEIGHT * SCALE; // size of canvas in pixels
  static constexpr int WIDTH_PX = WIDTH * SCALE; // size of canvas in pixels

  static constexpr int RADIUS_PX = 15; // for drawing Node

  static constexpr int NUM_STEPS = 10000; // how long to search for a path

  static constexpr int SHOW_DELAY = 10; // in ms

	static inline cv::Scalar WHITE = cv::Scalar(255, 255, 255);
	static inline cv::Scalar BLACK = cv::Scalar(0, 0, 0);
	static inline cv::Scalar RED = cv::Scalar(0, 0, 255);
	static inline cv::Scalar GREEN = cv::Scalar(0, 255, 0);
	static inline cv::Scalar BLUE = cv::Scalar(255, 0, 0);
	static inline cv::Scalar GRAY = cv::Scalar(100, 100, 100);

	static bool isInBounds(const double x, const double y) {
		if(x >=0 && x <= WIDTH && y>=0 && y <= HEIGHT) {
			return true;
		}
		return false;
	}

	static constexpr double EPSILON = 0.00001;

	static bool equals(double a, double b) {
	  if(abs(a - b) < EPSILON) {
	    return true;
	  }
	  return false;
	}

};

#endif