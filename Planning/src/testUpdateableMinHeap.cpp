#include <iostream>
#include <cassert>
#include "UpdateableMinHeap.h"
#include "DStarNode.h"
#include "DStarLite.h"

using namespace std;

// clang++ -std=c++20 testUpdateableMinHeap.cpp DStarNode.cpp StarNode.cpp Node.cpp -o testUpdateableMinHeap

template <typename T>
vector<T> extractMinHeap(UpdateableMinHeap<T> heap) {
  vector<T> vec;
  while(heap.getSize() > 0 ) {
    vec.push_back(heap.extractMin());
  }
  return vec;
}

template <typename T>
bool destructiveIsSorted(UpdateableMinHeap<T> heap) {
  T prev = heap.extractMin();
  T next;
  while(heap.getSize() > 0 ) {
    next = heap.extractMin();
    if(next < prev) {
      return false;
    }
  }
  return true;
}

void testUpdateableMinHeapSimple() {
  int a = 4, b = 3, c = 2, d = 1;
  vector<int*> ints = {&a, &b, &c, &d};
  UpdateableMinHeap<int*> umhInt(ints);
  assert(destructiveIsSorted(umhInt));

  cout << "  Passed testUpdateableMinHeapSimple" << endl;
}

void testUpdateableMinHeapDelete() {
  int a = 44, b = 332, c = 2, d = 1;
  vector<int*> ints = {&a, &b, &c, &d};
  UpdateableMinHeap<int*> umhInt(ints);
  assert(umhInt.getSize() == 4);
  umhInt.deleteValue(&b);
  assert(umhInt.getSize() == 3);
  assert(!umhInt.contains(&b));
  assert(destructiveIsSorted(umhInt));
  cout << "  Passed testUpdateableMinHeapDelete" << endl;
}

void testUpdateableMinHeapInsert() {
  int a = 14, b = 332, c = 2, d = 1, e = 500;
  vector<int*> ints = {&a, &b, &c, &d};
  UpdateableMinHeap<int*> umhInt(ints);
  assert(umhInt.getSize() == 4);
  umhInt.insertValue(&e);
  assert(umhInt.getSize() == 5);
  assert(destructiveIsSorted(umhInt));
}

void testUpdateableMinHeap_DStarNode() {
  UpdateableMinHeap<shared_ptr<DStarNode>> umhDStar;
  shared_ptr<DStarNode> goal = make_shared<DStarNode>("Goal", 100,99);
  shared_ptr<DStarNode> a = make_shared<DStarNode>("A", 1,0);
  shared_ptr<DStarNode> b = make_shared<DStarNode>("B", 50,24);
  shared_ptr<DStarNode> c = make_shared<DStarNode>("C", 92,95);
  a->computeHeuristic(goal); // hn = big
  b->computeHeuristic(goal); // hn = medium
  c->computeHeuristic(goal); // hn = small

  a->setGn(1);
  b->setGn(1);
  c->setGn(1);

  a->computeKey(0); 
  b->computeKey(0); 
  c->computeKey(0); 

  umhDStar.insertValue(a);
  umhDStar.insertValue(b);
  umhDStar.insertValue(c);

  assert(umhDStar.getSize() == 3);
  assert(umhDStar.contains(a));
  assert(umhDStar.contains(b));
  assert(umhDStar.contains(c));

  shared_ptr<DStarNode> first = umhDStar.extractMin();
  assert(first == c);

  assert(umhDStar.getSize() == 2);
  assert(umhDStar.contains(a));
  assert(umhDStar.contains(b));
  assert(!umhDStar.contains(c));
  shared_ptr<DStarNode> second = umhDStar.extractMin();
  assert(second == b);
  shared_ptr<DStarNode> third = umhDStar.extractMin();
  assert(third == a);
  cout << "  Passed testUpdateableMinHeap_DStarNode" << endl;
}

void testUpdateableMinHeap_DStarNodeSimple() {
  UpdateableMinHeap<shared_ptr<DStarNode>> umhDStar;
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

  umhDStar.insertValue(a);
  umhDStar.insertValue(b);

  auto min = umhDStar.extractMin();
  DStarNode::Key kfirst = min->getKey();
  assert(kfirst.k1 == 10);
  assert(kfirst.k2 == 2);
  cout << "  Passed testUpdateableMinHeap_DStarNodeSimple" << endl;
}

int main(int argc, char** argv) {
  cout << "Testing UpdateableMinHeap ..." << endl;
  testUpdateableMinHeapSimple();
   testUpdateableMinHeapDelete();

  cout << "Testing UpdateableMinHeap with DStarNodes ..." << endl;
  testUpdateableMinHeap_DStarNodeSimple();
   testUpdateableMinHeap_DStarNode();


  cout << "All tests passed!" << endl;
  return 0;
}














