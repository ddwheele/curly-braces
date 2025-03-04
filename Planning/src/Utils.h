#ifndef UTILS_H
#define UTILS_H

struct Utils {

  static constexpr int NUM_STEPS = 10000; // how long to search for a path

  static constexpr int SCALE = 50; // conversion from units to pixels for drawing

  static constexpr double HEIGHT = 10.0; // size of canvas in units (RRT)
  static constexpr double WIDTH = 10.0; // size of canvas in units (RRT)

	static constexpr double EPSILON = 0.00001;

	static bool equals(double a, double b) {
	  if(abs(a - b) < EPSILON) {
	    return true;
	  }
	  return false;
	}

};

#endif