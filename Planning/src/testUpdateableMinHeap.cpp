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

// template <typename T>
// void printPrimitiveVector(vector<T> vec) {
//   for(int i=0; i<vec.size(); i++) {
//     cout << vec[i] << " ";
//   }
//   cout << endl;
// }

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

// void testUpdateableMinHeapSimple() {
//   vector<int> ints = {4, 3, 2, 1};
//   UpdateableMinHeap<int> umhInt(ints);
//   assert(destructiveIsSorted(umhInt));

//   vector<float> floats = {47.3, 15.7, 0.001};
//   UpdateableMinHeap<float> umhFloat(floats);
//   assert(destructiveIsSorted(umhFloat));
//   cout << "  Passed testUpdateableMinHeapSimple" << endl;
// }

// void testUpdateableMinHeapDelete() {
//   vector<int> ints = {14, 332, 2, 1};
//   UpdateableMinHeap<int> umhInt(ints);
//   assert(umhInt.getSize() == 4);
//   umhInt.deleteValue(332);
//   assert(umhInt.getSize() == 3);
//   assert(destructiveIsSorted(umhInt));
//   cout << "  Passed testUpdateableMinHeapDelete" << endl;
// }

// void testUpdateableMinHeapInsert() {
//   UpdateableMinHeap<int> umhInt;
//   umhInt.insertValue(500);
//   umhInt.insertValue(100);
//   umhInt.insertValue(20);
//   assert(umhInt.getSize() == 3);
//   assert(destructiveIsSorted(umhInt));

//   vector<int> ints = {14, 332, 2, 1};
//   umhInt.resetValues(ints);
//   assert(umhInt.getSize() == 4);
//   umhInt.insertValue(500);
//   assert(umhInt.getSize() == 5);
//   assert(destructiveIsSorted(umhInt));

//   vector<float> floats = {47.3, 15.7, 0.001};
//   UpdateableMinHeap<float> umhFloat(floats);
//   assert(umhFloat.getSize() == 3);
//   umhFloat.insertValue(-4);
//   assert(umhFloat.getSize() == 4);
//   assert(destructiveIsSorted(umhFloat));

//   vector<double> doubles = {789.1, -17.01, 13.4, -239.8, 9009.3 };
//   UpdateableMinHeap<double> umhDouble(doubles);
//   assert(umhDouble.getSize() == 5);
//   umhDouble.insertValue(100);
//   assert(umhDouble.getSize() == 6);
//   assert(destructiveIsSorted(umhDouble));
//   cout << "  Passed testUpdateableMinHeapInsert" << endl;
// }

// void testUpdateableMinHeap() {
//   vector<int> someInts = {67, 85, 37, 24, 90, 15, 24, 1975, 12, 43, 44, 3, 2, 1};
//   UpdateableMinHeap<int> umh(someInts);
//   assert(destructiveIsSorted(umh));
//   cout << "  Passed testUpdateableMinHeap" << endl;
// }

void testUpdateableMinHeap_DStarNode() {
  UpdateableMinHeap<shared_ptr<DStarNode>> umhDStar;
  shared_ptr<DStarNode> goal = make_shared<DStarNode>("Goal", 11,0);
  shared_ptr<DStarNode> a = make_shared<DStarNode>("A", 1,0);
  shared_ptr<DStarNode> b = make_shared<DStarNode>("B", 3,0);
  shared_ptr<DStarNode> c = make_shared<DStarNode>("C", 11,2);
  a->computeHeuristic(goal); // hn = 10
  b->computeHeuristic(goal); // hn = 8
  c->computeHeuristic(goal); // hn = 2

  a->setGn(3);
  b->setGn(2);
  c->setGn(1);

  a->computeKey(0); // 10 + 3 + 0
  b->computeKey(0); // 8 + 2 + 0
  c->computeKey(1); // 2 + 1 + 1

  DStarNode::Key ak = a->getKey();
  assert(ak.k1 == 13);
  assert(ak.k2 == 3);

  DStarNode::Key bk = b->getKey();
  assert(bk.k1 == 10);
  assert(bk.k2 == 2);

  DStarNode::Key ck = c->getKey();
  assert(ck.k1 == 4);
  assert(ck.k2 == 1);

  umhDStar.insertValue(a);
  umhDStar.insertValue(b);
  umhDStar.insertValue(c);

  auto front = umhDStar.extractMin();
  DStarNode::Key kfirst = front->getKey();
  assert(kfirst.k1 == 4);
  assert(kfirst.k2 == 1);

  umhDStar.extractMin();

  front = umhDStar.extractMin();
  kfirst = front->getKey();
  assert(kfirst.k1 == 13);
  assert(kfirst.k2 == 3);
  cout << "  Passed testUpdateableMinHeap_DStarNode" << endl;
}

void testUpdateableMinHeap_DStarNodeSimple() {
  UpdateableMinHeap<shared_ptr<DStarNode>> umhDStar;
  shared_ptr<DStarNode> goal = make_shared<DStarNode>("Goal", 11,0);
  shared_ptr<DStarNode> a = make_shared<DStarNode>("A", 1,0);
  shared_ptr<DStarNode> b = make_shared<DStarNode>("B", 3,0);
  shared_ptr<DStarNode> c = make_shared<DStarNode>("C", 11,2);
  a->computeHeuristic(goal); // hn = 10
  b->computeHeuristic(goal); // hn = 8
  c->computeHeuristic(goal); // hn = 2

  a->setGn(3);
  b->setGn(2);
  c->setGn(1);

  a->computeKey(0); // 10 + 3 + 0
  b->computeKey(0); // 8 + 2 + 0
  c->computeKey(1); // 2 + 1 + 1

  DStarNode::Key ak = a->getKey();
  assert(ak.k1 == 13);
  assert(ak.k2 == 3);

  DStarNode::Key bk = b->getKey();
  assert(bk.k1 == 10);
  assert(bk.k2 == 2);

  DStarNode::Key ck = c->getKey();
  assert(ck.k1 == 4);
  assert(ck.k2 == 1);

  umhDStar.insertValue(a);
  umhDStar.insertValue(b);
 // umhDStar.insertValue(c);

  auto min = umhDStar.extractMin();
  cout<<"min node is:";
  min->printMe();
  DStarNode::Key kfirst = min->getKey();
  kfirst.printMe();
  assert(kfirst.k1 == 4);
  assert(kfirst.k2 == 1);

  // umhDStar.extractMin();

  // min = umhDStar.extractMin();
  // kfirst = min->getKey();
  // assert(kfirst.k1 == 13);
  // assert(kfirst.k2 == 3);
  cout << "  Passed testUpdateableMinHeap_DStarNodeSimple" << endl;
}
int main(int argc, char** argv) {
  // cout << "Testing UpdateableMinHeap ..." << endl;
  // testUpdateableMinHeapSimple();
  // testUpdateableMinHeap();
  // testUpdateableMinHeapInsert();
  // testUpdateableMinHeapDelete();

  cout << "Testing UpdateableMinHeap with DStarNodes ..." << endl;
  testUpdateableMinHeap_DStarNodeSimple();
  //  testUpdateableMinHeap_DStarNode();


  cout << "All tests passed!" << endl;
  return 0;
}














