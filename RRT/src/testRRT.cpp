#include <iostream>
#include <cassert>
#include "Node.h"
#include "Obstacle.h"
#include "RRT.h"

using namespace std;

double EPSILON = 0.00001;

bool equals(double a, double b) {
  if(abs(a - b) < EPSILON) {
    return true;
  }
  return false;
}

void testConstantsIsInBounds() {
  assert(Constants::isInBounds(Constants::WIDTH/2, Constants::HEIGHT/2));
  assert(!Constants::isInBounds(-10, Constants::HEIGHT));
  assert(!Constants::isInBounds(Constants::WIDTH, -12));
  assert(!Constants::isInBounds(Constants::WIDTH + 1,Constants::HEIGHT));
  assert(!Constants::isInBounds(Constants::WIDTH,Constants::HEIGHT + 1));
  cout << "  Passed testConstantsIsInBounds" << endl;
}

void testNodeDistanceTo() {
  Node n(1,1);
  assert(equals(n.distanceTo(3,1), 2));
  assert(equals(n.distanceTo(1,12), 11));

  Node n0(0,0);
  assert(equals(n0.distanceTo(-3,-4), 5));
  assert(equals(n.distanceTo(n0), sqrt(2)));

  cout << "  Passed testNodeDistanceTo" << endl;
}

void testObstaclePointIsInside() {
  Obstacle o(10,10,20,20);
  assert(o.pointIsInside(12,17));
  assert(!o.pointIsInside(1,17));
  assert(!o.pointIsInside(2,25));
  assert(!o.pointIsInside(5,5));
  assert(!o.pointIsInside(15,2));
  assert(!o.pointIsInside(15,27));
  assert(!o.pointIsInside(34,3));
  assert(!o.pointIsInside(57,11));
  assert(!o.pointIsInside(142,137));
  
  cout << "  Passed testObstaclePointIsInside" << endl;
}

void testObstacleIntersects() {
  Obstacle o(10,10,20,20);
  shared_ptr<Node> topLeft = make_shared<Node>(5,25);
  shared_ptr<Node> left = make_shared<Node>(5,15);
  shared_ptr<Node> bottomLeft = make_shared<Node>(5,5);
  shared_ptr<Node> top = make_shared<Node>(15,25);
  shared_ptr<Node> bottom = make_shared<Node>(15,5);
  shared_ptr<Node> topRight = make_shared<Node>(25,25);
  shared_ptr<Node> right = make_shared<Node>(25,15);
  shared_ptr<Node> bottomRight = make_shared<Node>(25,5);
  shared_ptr<Node> inObs = make_shared<Node>(15,15);

  shared_ptr<Node> parentInObstacle = make_shared<Node>(55,15);
  parentInObstacle->parent = inObs;

  // points inside obstacle
  assert(o.intersects(*inObs));
  assert(!o.intersects(*top));
  assert(o.intersects(*parentInObstacle));

  // line can't intersect obstacle
  shared_ptr<Node> toTheLeft = make_shared<Node>(4,35);
  toTheLeft->parent = bottomLeft;
  assert(!o.intersects(*toTheLeft));

  shared_ptr<Node> toTheRight = make_shared<Node>(40,13);
  toTheRight->parent = right;
  assert(!o.intersects(*toTheRight));

  shared_ptr<Node> above = make_shared<Node>(100,100);
  above->parent = topRight;
  assert(!o.intersects(*above));

  shared_ptr<Node> below = make_shared<Node>(14,6);
  below->parent = bottom;
  assert(!o.intersects(*below));

  cout << "  Passed testObstacleIntersects" << endl;
}

int main(int argc, char** argv) {
  cout << "Testing Constants ..." << endl;
  testConstantsIsInBounds();

  cout << "Testing Node ..." << endl;
  testNodeDistanceTo();

  cout << "Testing Obstacle" << endl;
  testObstaclePointIsInside();
  testObstacleIntersects();

  cout << "All tests passed!" << endl;
  return 0;
}














