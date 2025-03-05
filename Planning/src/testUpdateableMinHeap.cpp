#include <iostream>
#include <cassert>
#include "UpdateableMinHeap.h"

using namespace std;

// clang++ -std=c++20 testUpdateableMinHeap.cpp -o testUpdateableMinHeap

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
  UpdateableMinHeap<int> umh(ints);
  // vector<int> fromHeap = extractMinHeap(umh);
  // printPrimitiveVector(fromHeap);

  // vector<int> sorted = {1, 2, 3, 4};

  assert(destructiveIsSorted(umh));

  cout << "  Passed testUpdateableMinHeapSimple" << endl;
}

void testUpdateableMinHeap() {
  vector<int> someInts = {67, 85, 37, 24, 90, 15, 24, 1975, 12, 43, 44, 3, 2, 1};
  UpdateableMinHeap<int> umh(someInts);
  assert(destructiveIsSorted(umh));
  // vector<int> fromHeap = extractMinHeap(umh);
  // printPrimitiveVector(fromHeap);

  cout << "  Passed testUpdateableMinHeap" << endl;
}

int main(int argc, char** argv) {
  cout << "Testing UpdateableMinHeap ..." << endl;
  testUpdateableMinHeap();
  testUpdateableMinHeapSimple();

  cout << "All tests passed!" << endl;
  return 0;
}














