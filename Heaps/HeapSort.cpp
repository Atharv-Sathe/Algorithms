#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void maxHeapify(vector<int>& arr, int index, int arrSize) {
  // Assuming index of first node is 0
  int l = 2 * index + 1;
  int r = 2 * index + 2;
  int largest = index;
  if (l < arrSize && arr[l] > arr[index]) largest = l;

  if (r < arrSize && arr[r] > arr[largest]) largest = r;

  if (largest != index) {
    swap(arr[index], arr[largest]);
    maxHeapify(arr, largest, arrSize);
  }
}

void buildMaxHeap(vector<int>& arr) {
  int n = arr.size();
  for (int i = n / 2; i >= 0; i--) {
    maxHeapify(arr, i, n);
  }
}

void heapSort(vector<int>& arr) {
  int n = arr.size();
  buildMaxHeap(arr);

  for (int i = n - 1; i > 0; i--) {
    swap(arr[0], arr[i]);
    maxHeapify(arr, 0, i);
  }
}

int main() {
  vector<int> arr = {14, 9, 12, 13, 21, 8, 5, 15, 1, 17};

  cout << "Calling HeapSort\n"; 
  heapSort(arr);
  cout << "Sorting finished!\n";
  for (int i : arr) {
    cout << i << " ";
  }
  return 0;
}