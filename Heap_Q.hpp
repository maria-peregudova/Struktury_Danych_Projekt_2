#ifndef HEAP_HPP
#define HEAP_HPP

template <typename T>
class BinaryHeap { 
  private:
    struct Node {
      int priority;
      T data;

      Node() : priority(0), data() {}
      Node(int p, const T& d) : priority(p), data(d) {}
    };

    Node* heap;
    int capacity;
    int size;

    void resize() {
      capacity *= 2;
      Node* newHeap = new Node[capacity];
      for (int i = 0; i < size; i++) {
        newHeap[i] = heap[i];
      }
      delete[] heap;
      heap = newHeap;
    }

    void swapNodes(Node& a, Node& b) {
      Node temp = a;
      a = b;
      b = temp;
    }

    int parent(int i) {
      return (i - 1) / 2;
    }
    int leftChild(int i) {
      return 2 * i + 1;
    }
    int rightChild(int i) {
      return 2 * i + 2;
    }

    void heapifyUp(int i) {
      while (i > 0 && heap[parent(i)].priority < heap[i].priority) {
        swapNodes(heap[i], heap[parent(i)]);
        i = parent(i);
      }
    }

    void heapifyDown(int i) {
      int largest = i;
      int left = leftChild(i);
      int right = rightChild(i);

      if (left < size && heap[left].priority > heap[largest].priority) {
        largest = left;
      }
      if (right < size && heap[right].priority > heap[largest].priority) {
        largest = right;
      }
      if (largest != i) {
        swapNodes(heap[i], heap[largest]);
        heapifyDown(largest);
      }
    }

  public:

    BinaryHeap(int n = 4){
      size = 0;
      capacity = n;
      heap = new Node[capacity];
    }

    ~BinaryHeap() {
      delete[] heap;
    }

    int getSize() const {
      return size;
    }

    void add(const T& data, int priority) {
      if (size == capacity) {
        resize();
      }
      heap[size] = {priority, data}; 
      size++;
      heapifyUp(size - 1);
    }

    void remove() {
      if (size == 0) {
        return;
      }
      heap[0] = heap[size - 1];
      size--;
      heapifyDown(0);
    }

  T peek() const {
    if (size == 0) {
      std::cout << "ERROR: Pusta kolejka!" << std::endl;
      return T();
    }
    return heap[0].data;
  }

    void modifyPriority(const T& data, int newPriority) {
      for (int i = 0; i < size; i++) {
        if (heap[i].data == data) {
          int oldPriority = heap[i].priority;
          heap[i].priority = newPriority;

          if (newPriority > oldPriority) {
            heapifyUp(i);
          } else {
            heapifyDown(i);
          }
          break;
        }
      }
    }
};

#endif // HEAP_HPP