#include <iostream>
#include <cassert>
#include "DStarNode.h"
#include "DStarLite.h"

using namespace std;

// clang++ -std=c++20 testDStarNode.cpp DStarNode.cpp StarNode.cpp Node.cpp -o testDStarNode

void testDStarNodePtr() {
  priority_queue<shared_ptr<DStarNode>,vector<shared_ptr<DStarNode>>, DStarLite::DStarNodePtrCompare> q;
  shared_ptr<DStarNode> goal = make_shared<DStarNode>("Goal", 11,0);
  shared_ptr<DStarNode> a = make_shared<DStarNode>("A", 1,0);
  shared_ptr<DStarNode> b = make_shared<DStarNode>("B", 3,0);
  a->computeHeuristic(goal); // hn = 10
  b->computeHeuristic(goal); // hn = 8

  a->setGn(3);
  b->setGn(2);

  a->computeKey(0); // 10 + 3 + 0
  b->computeKey(0); // 8 + 2 + 0

  DStarNode::Key ak = a->getKey();
  assert(ak.k1 == 13);
  assert(ak.k2 == 3);

  DStarNode::Key bk = b->getKey();
  assert(bk.k1 == 10);
  assert(bk.k2 == 2);

  assert(ak > bk);
  cout << "ak > bk = " << (ak > bk) << endl;
  cout << "bk > ak = " << (bk > ak) << endl;

  cout << "b < a = " << (b < a) << endl;
  cout << "a > b = " << (a > b) << endl;

  assert(b < a);
  assert(a > b);

  cout << "  Passed testDStarNodePtr" << endl;
}

void testDStarNode() {
  shared_ptr<DStarNode> goal = make_shared<DStarNode>("Goal", 11,0);
  DStarNode a("A", 1,0);
  DStarNode b("B", 3,0);
  a.computeHeuristic(goal); // hn = 10
  b.computeHeuristic(goal); // hn = 8

  a.setGn(3);
  b.setGn(2);

  a.computeKey(0); // 10 + 3 + 0
  b.computeKey(0); // 8 + 2 + 0

  DStarNode::Key ak = a.getKey();
  assert(ak.k1 == 13);
  assert(ak.k2 == 3);

  DStarNode::Key bk = b.getKey();
  assert(bk.k1 == 10);
  assert(bk.k2 == 2);

  assert(ak > bk);

  cout << "b < a = " << (b < a) << endl;
  cout << "a > b = " << (a > b) << endl;

  assert(b < a);
  assert(a > b);

  cout << "  Passed testDStarNodePtr" << endl;
}

void testDStarNodeKey() {
  DStarNode::Key maxKey;
  DStarNode::Key key10_8(10,8);

  DStarNode::Key key10_6(10,6);
  DStarNode::Key key0_0(0,0);

  DStarNode::Key changes(0,0);

  assert(maxKey > key10_8);
  assert(key10_8 < maxKey);

  assert(key10_8 > key10_6);
  assert(key10_6 < key10_8);

  assert(key10_8 > key0_0);
  assert(key0_0 < key10_8);

  assert(key0_0 != key10_8);

  assert(key0_0 == changes);
  assert(changes < key10_8);

  changes.update(15,5);
  assert(key0_0 != changes);
  assert(changes > key10_8);

  cout << "  Passed testDStarNodeKey" << endl;
}

int main(int argc, char** argv) {
  cout << "Testing DStarNode ..." << endl;
  testDStarNodeKey();
  //testDStarNodePtr();
  testDStarNode();

  cout << "All tests passed!" << endl;
  return 0;
}














