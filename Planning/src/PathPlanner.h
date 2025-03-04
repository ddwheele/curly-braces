#ifndef PATH_PLANNER_H
#define PATH_PLANNER_H

#include "DrawMap.h"

class PathPlanner {
public:
	PathPlanner() : drawMap(*this) {}

	virtual void findPath() = 0;


protected:
	DrawMap drawMap;
};

#endif