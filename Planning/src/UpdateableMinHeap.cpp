#include <iostream>
#include <vector>
#include <climits>

#include "UpdateableMinHeap.h"

using namespace std;

// Compile with `clang++ -std=c++20 UpdateableMinHeap.cpp -o Astar`
template <typename T>
UpdateableMinHeap<T>::UpdateableMinHeap() {
  int defaultCapacity = 10;
  this->size = 0;
  this->capacity = defaultCapacity;
  this->array.resize(defaultCapacity);
}

template <typename T>
UpdateableMinHeap<T>::UpdateableMinHeap(const vector<T>& arr) {
  int cap = arr.size();
  this->size = 0;
  this->capacity = cap;
  this->array.resize(cap);

  buildHeap(arr);
}

// template <typename T>
// UpdateableMinHeap<T>::UpdateableMinHeap(int capacity) {
//   this->size = 0;
//   this->capacity = capacity;
//   this->array.resize(capacity);
// }

template <typename T>
// Function to restore heap order at index i. O(log n)
void  UpdateableMinHeap<T>::heapify(int i) {
  // Initialize smallest as root
  int smallest = i;    
  //  Find the Left child index
  int left = 2 * i + 1;    
    // Find the Right child index
  int right = 2 * i + 2;   

  // If left child is smaller than root
  if (left < size && array[left] < array[smallest])
      smallest = left;

  // If right child is smaller than the smallest so far
  if (right < size && array[right] < array[smallest])
      smallest = right;

  // If smallest is not root
  if (smallest != i) {
      swap(array[i], array[smallest]);  
      heapify(smallest);                
  }
}



template <typename T>
// Inserts a new node into the min heap.
void  UpdateableMinHeap<T>::insertNode(T value) {
  if (size == capacity) {
    // Resize the heap if necessary
    capacity *= 2;
    array.resize(capacity);
  }
  size++;
  int i = size - 1;
  array[i] = value;

  // while parent of i > child i
  while (i != 0 && array[(i - 1) / 2] > array[i]) {
    // swap child with parent
    swap(array[i], array[(i - 1) / 2]);
    // consider parent of i to be child
    i = (i - 1) / 2;
  }
}

// Deletes a specific node from the min heap and ensures that the min heap 
// property is maintained after deletion. O(log n)
template <typename T>
void  UpdateableMinHeap<T>::deleteNode(T node) {
  // Find the index of the key
  int index = -1;
  for (int i = 0; i < size; ++i) {
    if (array[i] == node) {
      index = i;
      break;
    }
  }
  // If node is not found, return
  if (index == -1) {
    cout << "Node not found" << endl;
    return;
  }

  if (index == size - 1) {
    size--;
    return;
  }

  // Move the last element to the index of the node to be deleted
  array[index] = array[size - 1];
  size--;

  // Heapify down to heapify the rest of the min heap
  heapify(index);
}

// Returns the topmost element of the min heap. O(1)
template <typename T>
T  UpdateableMinHeap<T>::peek() const {
  if (size <= 0)
    throw std::range_error("UpdateableMinHeap is empty!");
  return array[0];
}

// Removes the root node of the min heap and heapifies the remaining heap. O(log n)
template <typename T>
T  UpdateableMinHeap<T>::extractMin() {
  if (size <= 0)
    throw std::range_error("UpdateableMinHeap is empty!");
  if (size == 1) {
    size--;
    return array[0];
  }

  // Store the minimum value, and remove it
  T root = array[0];
  array[0] = array[size - 1];
  size--;
  // Heapify the root node after deletion
  heapify(0);  
  return root;
}

// Builds a min heap from a given array.
template <typename T>
void UpdateableMinHeap<T>::buildHeap(const vector<T>& arr) {
  capacity = arr.size();
  size = capacity;
  array = arr;

  // Heapify the (n-1)/2 nodes
  for (int i = (size - 1) / 2; i >= 0; i--) {
    heapify(i);
  }
}

  // Function to print the values of  the  min heap. O(n)
template <typename T>
void UpdateableMinHeap<T>::printMe() const {
    for (int i = 0; i < size; ++i)
        cout << array[i] << " ";
    cout << endl;
}