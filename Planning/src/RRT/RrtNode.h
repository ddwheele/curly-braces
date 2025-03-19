#ifndef RRT_NODE_H
#define RRT_NODE_H

#include "Node.h"
#include "Utils.h"

class RrtNode : public Node {
public:
	shared_ptr<RrtNode> parent;

  RrtNode(const double _x, const double _y, const shared_ptr<RrtNode>& _parent = nullptr) 
      : Node(_x, _y), parent(_parent) {
  };

  /**
   * Inputs
   * - papa - node that needs to grow
   * - rx - x coord to grow toward
   * - ry - y coord to grow toward
   * 
   * returns ptr to Node that is STEP_SIZE toward rx, ry, with papa as parent
   */
  static shared_ptr<RrtNode> growToward(const shared_ptr<RrtNode>& papa,
       const double rx, const double ry, const double stepSize) {
  	double xdist = rx - papa->x;
    double ydist = ry - papa->y;

    double len = sqrt(xdist*xdist + ydist*ydist);

    double newX, newY;
    if(Utils::equals(len, 0)) {
      // could be more random, but ...
      newX = papa->x + stepSize;
      newY = papa->y + stepSize;
    } else {
      newX = papa->x + xdist/len*stepSize;
      newY = papa->y + ydist/len*stepSize;
    } 
    return make_shared<RrtNode>(newX, newY, papa);
  }
};

#endif
