#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// Function to perform Kahn's Algorithm for topological sorting
vector<int> kahnsAlgo(vector<vector<int>>& adjList) {
  int nodeCount = adjList.size();

  // Compute in-degree (number of incoming edges) for each node
  vector<int> inDegree(nodeCount, 0);
  for (int i = 0; i < nodeCount; i++) {
    for (int j : adjList[i]) {
      inDegree[j]++;
    }
  }

  // Queue to store nodes with in-degree 0
  queue<int> q;
  for (int i = 0; i < nodeCount; i++) {
    if (inDegree[i] == 0) q.push(i);
  }

  int loc = 0;
  vector<int> order(nodeCount, 0); // Stores the topological order
  while (!q.empty()) {
    int node = q.front();
    q.pop();
    order[loc++] = node;
    // For each neighbor, decrease its in-degree by 1
    for (int i : adjList[node]) {
      inDegree[i]--;
      // If in-degree becomes 0, add to queue
      if (inDegree[i] == 0) q.push(i);
    }
  }

  // If not all nodes are processed, there is a cycle
  if (loc != nodeCount) return {-1};  // There is a cycle in the graph
  return order;
}

int main() { return 0; }