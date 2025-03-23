#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
  Max-Heap : value of i <= value of parent
*/

void maxHeapify(vector<int>& arr, int index) {
  // Assuming index of first node is 0
  int l = 2 * index + 1;
  int r = 2 * index + 2;
  int largest = index;
  if (l < arr.size() && arr[l] > arr[index]) largest = l;

  if (r < arr.size() && arr[r] > arr[largest]) largest = r;

  if (largest != index) {
    swap(arr[index], arr[largest]);
    maxHeapify(arr, largest);
  }
}

void buildMaxHeap(vector<int>& arr) {
  int n = arr.size();
  for (int i = n / 2; i >= 0; i--) {
    maxHeapify(arr, i);
  }
}

int main() {
  
  vector<int> arr = {14, 9, 12, 13, 21, 8, 5, 15, 1, 17};

  buildMaxHeap(arr);
  
  for (int i : arr) {
    cout << i << " ";
  }

  return 0;
}