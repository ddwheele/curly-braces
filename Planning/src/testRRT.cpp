#include <iostream>
#include <cassert>
#include "Node.h"
#include "RrtNode.h"
#include "Obstacle.h"
#include "RRT.h"

using namespace std;

void testRrtFindNearest() {
  vector<shared_ptr<RrtNode>> vec;

  for(int i=0; i<6; i++) {
    vec.push_back(make_shared<RrtNode>(1,i));
  }

  RRT rrt(make_shared<RrtNode>(0,0), make_shared<RrtNode>(1,1), vector<Obstacle>());

  shared_ptr<RrtNode> near = rrt.findNearest(vec, 3, 3);
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
  shared_ptr<RrtNode> papa = make_shared<RrtNode>(0,0);
  double stepSize = 1;

  shared_ptr<RrtNode> seymour = RrtNode::growToward(papa, 0, 12, stepSize);
  assert(Constants::equals(seymour->x, 0));
  assert(Constants::equals(seymour->y, stepSize));
  assert(seymour->parent == papa);

  shared_ptr<RrtNode> joe = RrtNode::growToward(papa, 20, 0, stepSize);
  assert(Constants::equals(joe->x, stepSize));
  assert(Constants::equals(joe->y, 0));
  assert(joe->parent == papa);

  shared_ptr<RrtNode> neg = RrtNode::growToward(papa, -5, -5, stepSize);
  assert(Constants::equals(neg->x, -stepSize/sqrt(2.0)));
  assert(Constants::equals(neg->y, -stepSize/sqrt(2.0)));
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
  shared_ptr<RrtNode> topLeft = make_shared<RrtNode>(5,25);
  shared_ptr<RrtNode> left = make_shared<RrtNode>(5,15);
  shared_ptr<RrtNode> bottomLeft = make_shared<RrtNode>(5,5);
  shared_ptr<RrtNode> top = make_shared<RrtNode>(15,25);
  shared_ptr<RrtNode> bottom = make_shared<RrtNode>(15,5);
  shared_ptr<RrtNode> topRight = make_shared<RrtNode>(25,25);
  shared_ptr<RrtNode> right = make_shared<RrtNode>(25,15);
  shared_ptr<RrtNode> bottomRight = make_shared<RrtNode>(25,5);
  shared_ptr<RrtNode> inObs = make_shared<RrtNode>(15,15);

  shared_ptr<RrtNode> parentInObstacle = make_shared<RrtNode>(55,15);
  parentInObstacle->parent = inObs;

  // points inside obstacle
  assert(o.intersects(*inObs));
  assert(!o.intersects(*top));
  assert(o.intersects(*parentInObstacle));

  // line can't intersect obstacle
  shared_ptr<RrtNode> toTheLeft = make_shared<RrtNode>(4,35);
  toTheLeft->parent = bottomLeft;
  assert(!o.intersects(*toTheLeft));

  shared_ptr<RrtNode> toTheRight = make_shared<RrtNode>(40,13);
  toTheRight->parent = right;
  assert(!o.intersects(*toTheRight));

  shared_ptr<RrtNode> above = make_shared<RrtNode>(100,100);
  above->parent = topRight;
  assert(!o.intersects(*above));

  shared_ptr<RrtNode> below = make_shared<RrtNode>(14,6);
  below->parent = bottom;
  assert(!o.intersects(*below));

  // test vertical lines
  shared_ptr<RrtNode> verticalInside = make_shared<RrtNode>(15,16);
  verticalInside->parent = inObs;
  assert(o.intersects(*verticalInside));

  shared_ptr<RrtNode> verticalAcross = make_shared<RrtNode>(15,1);
  verticalAcross->parent = top;
  assert(o.intersects(*verticalAcross));

  shared_ptr<RrtNode> verticalParentInside = make_shared<RrtNode>(15,1);
  verticalParentInside->parent = inObs;
  assert(o.intersects(*verticalParentInside));

  shared_ptr<RrtNode> verticalRrtNodeInside = make_shared<RrtNode>(15,17);
  verticalRrtNodeInside->parent = top;
  assert(o.intersects(*verticalRrtNodeInside));

  shared_ptr<RrtNode> verticalAbove = make_shared<RrtNode>(15,40);
  verticalAbove->parent = top;
  assert(!o.intersects(*verticalAbove));

  shared_ptr<RrtNode> verticalBelow = make_shared<RrtNode>(15,9);
  verticalBelow->parent = bottom;
  assert(!o.intersects(*verticalBelow));

  shared_ptr<RrtNode> verticalToLeft = make_shared<RrtNode>(5,100);
  verticalToLeft->parent = bottomLeft;
  assert(!o.intersects(*verticalToLeft));

  shared_ptr<RrtNode> verticalToRight = make_shared<RrtNode>(25,3.2);
  verticalToRight->parent = topRight;
  assert(!o.intersects(*verticalToRight));

  // test cutting off corners
  shared_ptr<RrtNode> cutsTopRight = make_shared<RrtNode>(21,10);
  cutsTopRight->parent = top;
  assert(o.intersects(*cutsTopRight));

  shared_ptr<RrtNode> cutsTopRight2 = make_shared<RrtNode>(21,15);
  cutsTopRight2->parent = top;
  assert(o.intersects(*cutsTopRight2));

  shared_ptr<RrtNode> doesntCutTopRight = make_shared<RrtNode>(45,10);
  doesntCutTopRight->parent = top;
  assert(!o.intersects(*doesntCutTopRight));

  shared_ptr<RrtNode> cutsBottomRight = make_shared<RrtNode>(11,9);
  cutsBottomRight->parent = right;
  assert(o.intersects(*cutsBottomRight));

  shared_ptr<RrtNode> doesntCutBottomRight = make_shared<RrtNode>(15,1);
  doesntCutBottomRight->parent = right;
  assert(!o.intersects(*doesntCutBottomRight));

  shared_ptr<RrtNode> leftCutsTopLeft = make_shared<RrtNode>(9,15);
  leftCutsTopLeft->parent = top;
  assert(o.intersects(*leftCutsTopLeft));

  shared_ptr<RrtNode> leftDoesntCutTopLeft = make_shared<RrtNode>(11,40);
  leftDoesntCutTopLeft->parent = left;
  assert(!o.intersects(*leftDoesntCutTopLeft));

  shared_ptr<RrtNode> leftCutsBottomLeft = make_shared<RrtNode>(19,9);
  leftCutsBottomLeft->parent = left;
  assert(o.intersects(*leftCutsBottomLeft));

  shared_ptr<RrtNode> leftDoesntCutBottomLeft = make_shared<RrtNode>(11,2);
  leftDoesntCutBottomLeft->parent = left;
  assert(!o.intersects(*leftDoesntCutBottomLeft));

  shared_ptr<RrtNode> upperLeftAbove = make_shared<RrtNode>(100,19);
  upperLeftAbove->parent = topLeft;
  assert(!o.intersects(*upperLeftAbove));

  shared_ptr<RrtNode> upperLeftBelow = make_shared<RrtNode>(11,2);
  upperLeftBelow->parent = topLeft;
  assert(!o.intersects(*upperLeftBelow));

  shared_ptr<RrtNode> upperLeftHits = make_shared<RrtNode>(15,9);
  upperLeftHits->parent = topLeft;
  assert(o.intersects(*upperLeftHits));

  shared_ptr<RrtNode> cutsAcrossBottom = make_shared<RrtNode>(5,10);
  cutsAcrossBottom->parent = right;
  assert(o.intersects(*cutsAcrossBottom));

  shared_ptr<RrtNode> cutsThrough = make_shared<RrtNode>(6,18);
  cutsThrough->parent = right;
  assert(o.intersects(*cutsThrough));

  shared_ptr<RrtNode> lowerLeftAbove = make_shared<RrtNode>(15,50);
  lowerLeftAbove->parent = bottomLeft;
  assert(!o.intersects(*lowerLeftAbove));

  shared_ptr<RrtNode> lowerLeftBelow = make_shared<RrtNode>(40,11);
  lowerLeftBelow->parent = bottomLeft;
  assert(!o.intersects(*lowerLeftBelow));

  shared_ptr<RrtNode> lowerLeftHits = make_shared<RrtNode>(21,15);
  lowerLeftHits->parent = bottomLeft;
  assert(o.intersects(*lowerLeftHits));

  // vertical boundary
  shared_ptr<RrtNode> leftIsMinX = make_shared<RrtNode>(10,25);
  leftIsMinX->parent = bottom;
  assert(o.intersects(*leftIsMinX));

  shared_ptr<RrtNode> leftIsMaxX = make_shared<RrtNode>(20,11);
  leftIsMinX->parent  = make_shared<RrtNode>(20.1,25);
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














