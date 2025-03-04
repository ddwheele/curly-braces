#ifndef PATH_PLANNER_H
#define PATH_PLANNER_H

class PathPlanner {
public:
	virtual void findPath() = 0;
	virtual ~PathPlanner() = default;
};

#endif