#include <iostream>
#include <cassert>
#include "UpdateableMinHeap.h"

using namespace std;

// clang++ -std=c++20 UpdateableMinHeap.cpp testUpdateableMinHeap.cpp -o testUpdateableMinHeap

void testUpdateableMinHeap() {
  vector<int> someInts = {67, 85, 37, 24, 90, 15, 24, 1975, 12, 43, 44, 3, 2, 1};
  UpdateableMinHeap umh(someInts);
  umh.printMe();


  cout << "  Passed testUpdateableMinHeap" << endl;
}

int main(int argc, char** argv) {
  cout << "Testing UpdateableMinHeap ..." << endl;
  testUpdateableMinHeap();

  cout << "All tests passed!" << endl;
  return 0;
}














