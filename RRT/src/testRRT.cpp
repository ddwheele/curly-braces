#include <iostream>
#include <cassert>
#include "Node.h"
#include "Obstacle.h"
#include "RRT.h"

using namespace std;

void testRrtFindNearest() {
  vector<shared_ptr<Node>> vec;

  for(int i=0; i<6; i++) {
    vec.push_back(make_shared<Node>(1,i));
  }

  RRT rrt(make_shared<Node>(0,0), make_shared<Node>(1,1), vector<Obstacle>());

  shared_ptr<Node> near = rrt.findNearest(vec, 3, 3);
  assert(Constants::equals(near->x, 1));
  assert(Constants::equals(near->y, 3));

  cout << "  Passed testRrtFindNearest" << endl;
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
  assert(Constants::equals(n.distanceTo(3,1), 2));
  assert(Constants::equals(n.distanceTo(1,12), 11));

  Node n0(0,0);
  assert(Constants::equals(n0.distanceTo(-3,-4), 5));
  assert(Constants::equals(n.distanceTo(n0), sqrt(2)));

  cout << "  Passed testNodeDistanceTo" << endl;
}

void testNodeGrowToward() {
  shared_ptr<Node> papa = make_shared<Node>(0,0);

  shared_ptr<Node> seymour = Node::growToward(papa, 0, 12);
  assert(Constants::equals(seymour->x, 0));
  assert(Constants::equals(seymour->y, Constants::STEP_SIZE));
  assert(seymour->parent == papa);

  shared_ptr<Node> joe = Node::growToward(papa, 20, 0);
  assert(Constants::equals(joe->x, Constants::STEP_SIZE));
  assert(Constants::equals(joe->y, 0));
  assert(joe->parent == papa);

  shared_ptr<Node> neg = Node::growToward(papa, -5, -5);
  assert(Constants::equals(neg->x, -Constants::STEP_SIZE/sqrt(2.0)));
  assert(Constants::equals(neg->y, -Constants::STEP_SIZE/sqrt(2.0)));
  assert(neg->parent == papa);

  cout << "  Passed testNodeGrowToward" << endl;
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

  // test vertical lines
  shared_ptr<Node> verticalInside = make_shared<Node>(15,16);
  verticalInside->parent = inObs;
  assert(o.intersects(*verticalInside));

  shared_ptr<Node> verticalAcross = make_shared<Node>(15,1);
  verticalAcross->parent = top;
  assert(o.intersects(*verticalAcross));

  shared_ptr<Node> verticalParentInside = make_shared<Node>(15,1);
  verticalParentInside->parent = inObs;
  assert(o.intersects(*verticalParentInside));

  shared_ptr<Node> verticalNodeInside = make_shared<Node>(15,17);
  verticalNodeInside->parent = top;
  assert(o.intersects(*verticalNodeInside));

  shared_ptr<Node> verticalAbove = make_shared<Node>(15,40);
  verticalAbove->parent = top;
  assert(!o.intersects(*verticalAbove));

  shared_ptr<Node> verticalBelow = make_shared<Node>(15,9);
  verticalBelow->parent = bottom;
  assert(!o.intersects(*verticalBelow));

  shared_ptr<Node> verticalToLeft = make_shared<Node>(5,100);
  verticalToLeft->parent = bottomLeft;
  assert(!o.intersects(*verticalToLeft));

  shared_ptr<Node> verticalToRight = make_shared<Node>(25,3.2);
  verticalToRight->parent = topRight;
  assert(!o.intersects(*verticalToRight));

  // test cutting off corners
  shared_ptr<Node> cutsTopRight = make_shared<Node>(21,10);
  cutsTopRight->parent = top;
  assert(o.intersects(*cutsTopRight));

  shared_ptr<Node> cutsTopRight2 = make_shared<Node>(21,15);
  cutsTopRight2->parent = top;
  assert(o.intersects(*cutsTopRight2));

  shared_ptr<Node> doesntCutTopRight = make_shared<Node>(45,10);
  doesntCutTopRight->parent = top;
  assert(!o.intersects(*doesntCutTopRight));

  shared_ptr<Node> cutsBottomRight = make_shared<Node>(11,9);
  cutsBottomRight->parent = right;
  assert(o.intersects(*cutsBottomRight));

  shared_ptr<Node> doesntCutBottomRight = make_shared<Node>(15,1);
  doesntCutBottomRight->parent = right;
  assert(!o.intersects(*doesntCutBottomRight));

  shared_ptr<Node> leftCutsTopLeft = make_shared<Node>(9,15);
  leftCutsTopLeft->parent = top;
  assert(o.intersects(*leftCutsTopLeft));

  shared_ptr<Node> leftDoesntCutTopLeft = make_shared<Node>(11,40);
  leftDoesntCutTopLeft->parent = left;
  assert(!o.intersects(*leftDoesntCutTopLeft));

  shared_ptr<Node> leftCutsBottomLeft = make_shared<Node>(19,9);
  leftCutsBottomLeft->parent = left;
  assert(o.intersects(*leftCutsBottomLeft));

  shared_ptr<Node> leftDoesntCutBottomLeft = make_shared<Node>(11,2);
  leftDoesntCutBottomLeft->parent = left;
  assert(!o.intersects(*leftDoesntCutBottomLeft));

  shared_ptr<Node> upperLeftAbove = make_shared<Node>(100,19);
  upperLeftAbove->parent = topLeft;
  assert(!o.intersects(*upperLeftAbove));

  shared_ptr<Node> upperLeftBelow = make_shared<Node>(11,2);
  upperLeftBelow->parent = topLeft;
  assert(!o.intersects(*upperLeftBelow));

  shared_ptr<Node> upperLeftHits = make_shared<Node>(15,9);
  upperLeftHits->parent = topLeft;
  assert(o.intersects(*upperLeftHits));

  shared_ptr<Node> cutsAcrossBottom = make_shared<Node>(5,10);
  cutsAcrossBottom->parent = right;
  assert(o.intersects(*cutsAcrossBottom));

  shared_ptr<Node> cutsThrough = make_shared<Node>(6,18);
  cutsThrough->parent = right;
  assert(o.intersects(*cutsThrough));

  shared_ptr<Node> lowerLeftAbove = make_shared<Node>(15,50);
  lowerLeftAbove->parent = bottomLeft;
  assert(!o.intersects(*lowerLeftAbove));

  shared_ptr<Node> lowerLeftBelow = make_shared<Node>(40,11);
  lowerLeftBelow->parent = bottomLeft;
  assert(!o.intersects(*lowerLeftBelow));

  shared_ptr<Node> lowerLeftHits = make_shared<Node>(21,15);
  lowerLeftHits->parent = bottomLeft;
  assert(o.intersects(*lowerLeftHits));

  // vertical boundary
  shared_ptr<Node> leftIsMinX = make_shared<Node>(10,25);
  leftIsMinX->parent = bottom;
  assert(o.intersects(*leftIsMinX));

  shared_ptr<Node> leftIsMaxX = make_shared<Node>(20,11);
  leftIsMinX->parent  = make_shared<Node>(20.1,25);
  assert(!o.intersects(*leftIsMinX));

  cout << "  Passed testObstacleIntersects" << endl;
}

int main(int argc, char** argv) {
  cout << "Testing Constants ..." << endl;
  testConstantsIsInBounds();

  cout << "Testing Node ..." << endl;
  testNodeDistanceTo();
  testNodeGrowToward();

  cout << "Testing Obstacle" << endl;
  testObstaclePointIsInside();
  testObstacleIntersects();

  cout << "Testing RRT" << endl;
  testRrtFindNearest();

  cout << "All tests passed!" << endl;
  return 0;
}














