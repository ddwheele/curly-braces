#include <iostream>
#include <cassert>
#include "UpdateableMinHeap.h"
#include "DStarNode.h"

using namespace std;

// clang++ -std=c++20 testUpdateableMinHeap.cpp -o testUpdateableMinHeap
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
void printPrimitiveVector(vector<T> vec) {
  for(int i=0; i<vec.size(); i++) {
    cout << vec[i] << " ";
  }
  cout << endl;
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
  vector<int> ints = {4, 3, 2, 1};
  UpdateableMinHeap<int> umhInt(ints);
  assert(destructiveIsSorted(umhInt));

  vector<float> floats = {47.3, 15.7, 0.001};
  UpdateableMinHeap<float> umhFloat(floats);
  assert(destructiveIsSorted(umhFloat));
  cout << "  Passed testUpdateableMinHeapSimple" << endl;
}

void testUpdateableMinHeapInsert() {
  vector<int> ints = {14, 332, 2, 1};
  UpdateableMinHeap<int> umhInt(ints);
  umhInt.insertValue(500);
  assert(destructiveIsSorted(umhInt));

  vector<float> floats = {47.3, 15.7, 0.001};
  UpdateableMinHeap<float> umhFloat(floats);
  umhFloat.insertValue(-4);
  assert(destructiveIsSorted(umhFloat));

  vector<double> doubles = {789.1, -17.01, 13.4, -239.8, 9009.3 };
  UpdateableMinHeap<double> umhDouble(doubles);
  umhDouble.insertValue(100);
  assert(destructiveIsSorted(umhDouble));
  cout << "  Passed testUpdateableMinHeapInsert" << endl;
}

void testUpdateableMinHeapDelete() {
  vector<int> ints = {14, 332, 2, 1};
  UpdateableMinHeap<int> umhInt(ints);
  assert(umhInt.getSize() == 4);
  umhInt.insertValue(500);
  assert(umhInt.getSize() == 5);
  assert(destructiveIsSorted(umhInt));

  vector<float> floats = {47.3, 15.7, 0.001};
  UpdateableMinHeap<float> umhFloat(floats);
  assert(umhFloat.getSize() == 3);
  umhFloat.insertValue(-4);
  assert(umhFloat.getSize() == 4);
  assert(destructiveIsSorted(umhFloat));

  vector<double> doubles = {789.1, -17.01, 13.4, -239.8, 9009.3 };
  UpdateableMinHeap<double> umhDouble(doubles);
  assert(umhDouble.getSize() == 5);
  umhDouble.insertValue(100);
  assert(umhDouble.getSize() == 6);
  assert(destructiveIsSorted(umhDouble));
  cout << "  Passed testUpdateableMinHeapDelete" << endl;
}

void testUpdateableMinHeap() {
  vector<int> someInts = {67, 85, 37, 24, 90, 15, 24, 1975, 12, 43, 44, 3, 2, 1};
  UpdateableMinHeap<int> umh(someInts);
  assert(destructiveIsSorted(umh));
 
  cout << "  Passed testUpdateableMinHeap" << endl;
}

int main(int argc, char** argv) {
  cout << "Testing UpdateableMinHeap ..." << endl;
  testUpdateableMinHeapSimple();
  testUpdateableMinHeap();
  testUpdateableMinHeapInsert();
  testUpdateableMinHeapDelete();


  cout << "All tests passed!" << endl;
  return 0;
}














