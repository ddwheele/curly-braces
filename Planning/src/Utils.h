#ifndef UTILS_H
#define UTILS_H

#include <limits>
#include <format>

using namespace std;

struct Utils {

  static constexpr int NUM_STEPS = 10000; // how long to search for a path

  static constexpr int SCALE = 70; // conversion from units to pixels for drawing

  static constexpr double HEIGHT = 20.0; // size of canvas in units (RRT)
  static constexpr double WIDTH = 20.0; // size of canvas in units (RRT)

	static constexpr double EPSILON = 0.00001;

	static bool equals(const double a, const double b) {
	  if(abs(a - b) < EPSILON) {
	    return true;
	  }
	  return false;
	}

	static string infString(const double d) {
		if(equals(d, numeric_limits<double>::max()) || equals(d, numeric_limits<float>::max())) {
			return "inf";
		}
		return std::format("{:.1f}", d);
	}

};

#endif