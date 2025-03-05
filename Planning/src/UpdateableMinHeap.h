#ifndef UPDATEABLE_MIN_HEAP
#define UPDATEABLE_MIN_HEAP

// A min-heap is a complete binary tree in which the value of each node is less than the value of its left child and right child.
template <typename T>
class UpdateableMinHeap {
public:
  UpdateableMinHeap();

  UpdateableMinHeap(const std::vector<T>& arr);

  //UpdateableMinHeap(int capacity);

  // Inserts a new node into the min heap.
  void insertNode(T node);

  // Deletes a specific node from the min heap and ensures that the min heap property is maintained after deletion.
  void deleteNode(T node);

  // Returns the topmost element of the min heap.
  T peek() const;

  // Removes the root node of the min heap and heapifies the remaining heap.
  T extractMin();

  void printMe() const;

private:
  std::vector<T> array;  
  int size;         
  int capacity;

  // Rearranges the position of elements to ensure that the min heap property is maintained at i
  void heapify(int i);

  // Builds a min heap from a given array.
  void buildHeap(const std::vector<T>& arr);
};

#endif