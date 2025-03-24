#ifndef UPDATEABLE_MIN_HEAP
#define UPDATEABLE_MIN_HEAP

#include <iostream>

using namespace std;

// ONLY WORKS FOR POINTER TYPES

/**
 * Provides a min-heap implementation that allows for deletion of current nodes. 
 * Meant to be used for D* Lite
 * 
 * A min-heap is a complete binary tree in which the value of each node is less than 
 * the value of its left child and right child.
 */
template <typename T>
class UpdateableMinHeap {
public:
  UpdateableMinHeap() {
    int defaultCapacity = 10;
    this->size = 0;
    this->capacity = defaultCapacity;
    this->data.resize(defaultCapacity);
  }

  UpdateableMinHeap(const vector<T>& arr) {
    int cap = arr.size();
    this->size = 0;
    this->capacity = cap;
    this->data.resize(cap);

    buildHeap(arr);
  }

  // remove all data from MinHeap
  void clear() {
    int defaultCapacity = 10;
    this->size = 0;
    this->capacity = defaultCapacity;
    this->data.resize(defaultCapacity);
  }

  bool contains(const T& value) {
    for(int i=0; i<size; i++) {
      if(data[i] == value) {
        return true;
      }
    }
    return false;
  }

  // Inserts a new node into the min heap.
  void insertNode(const T& value) {
    if (size == capacity) {
      // Resize the heap if necessary
      capacity *= 2;
      data.resize(capacity);
    }
    size++;
    int i = size - 1;
    // put new value at the end
    data[i] = value;

    // while parent of i > child i
    while (i != 0 && (*data[(i - 1) / 2] > *data[i])) {
      // swap child with parent
      swap(data[i], data[(i - 1) / 2]);
      // consider parent of i to be child
      i = (i - 1) / 2;
    }
  }

  // Deletes a specific node from the min heap and ensures that the min heap property is maintained after deletion.
  void deleteNode(const T& node) {
    // Find the index of the key
    int index = -1;
    for (int i = 0; i < size; ++i) {
      if (data[i] == node) {
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
    data[index] = data[size - 1];
    size--;

    // Heapify down to heapify the rest of the min heap
    heapify(index);
  }

  // Returns the topmost element of the min heap.
  T peek() const {
    if (size <= 0)
      throw std::range_error("UpdateableMinHeap is empty!");
    return data[0];
  }

  // Removes the root node of the min heap and heapifies the remaining heap.
  T extractMin() {
    if (size <= 0)
      throw std::range_error("UpdateableMinHeap is empty!");
    if (size == 1) {
      size--;
      return data[0];
    }

    // Store the minimum value, and remove it
    T root = data[0];
    data[0] = data[size - 1];
    size--;
    // Heapify the root node after deletion
    heapify(0);  
    return root;
  }

  int getSize() const {
    return size;
  }

  // recreates the min heap with these values
  void resetValues(const vector<T>& arr) {
    buildHeap(arr);
  }

  void printMe() {
    cout << "UMinHeap = ";
    for (int i=0;i<size; i++) {
       cout <<"\t" <<*data[i] <<endl;
    }
  }

private:
  std::vector<T> data;  
  int size;         
  int capacity;

  // Rearranges the position of elements to ensure that the min heap property is maintained at i
  void heapify(int i) {
    // Initialize smallest as root
    int smallest = i;    
    //  Find the Left child index
    int left = 2 * i + 1;    
      // Find the Right child index
    int right = 2 * i + 2;   

    // If left child is smaller than root
    if (left < size && (*data[left] < *data[smallest]))
        smallest = left;

    // If right child is smaller than the smallest so far
    if (right < size && (*data[right] < *data[smallest]))
        smallest = right;

    // If smallest is not root
    if (smallest != i) {
        // make the root the smallest thing
        swap(data[i], data[smallest]);
        // heapify the child that was swapped (down to the leaf)
        heapify(smallest);                
    }
  }

  // Builds a min heap from a given data.
  void buildHeap(const vector<T>& arr) {
    capacity = arr.size();
    size = capacity;
    data = arr;

    // Heapify the (n-1)/2 nodes
    for (int i = (size - 1) / 2; i >= 0; i--) {
      heapify(i);
    }
  }
};

#endif