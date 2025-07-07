#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// Function to find sum of weights of edges of the Minimum Spanning Tree.
// Lazy Prims Algorithm
// This is called lazy because the priority queue may contain a lot of stale
// nodes.
int spanningTree(int V, vector<vector<int>> adj[]) {
  // PQ : {cost, node}
  priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;

  // Starting from node 0, push all edges of node to pq
  for (auto& edge : adj[0]) {
    pq.push({edge[1], edge[0]});
  }

  vector<bool> visited(V, false);
  visited[0] = true;
  int totalCost = 0;
  int edgeCount = 0;
  while (!pq.empty() && edgeCount < V - 1) {
    int cost = pq.top()[0], node = pq.top()[1];
    pq.pop();

    if (visited[node]) continue;

    totalCost += cost;
    edgeCount++;

    visited[node] = true;

    for (auto& edge : adj[node]) {
      if (visited[edge[0]]) continue;
      pq.push({edge[1], edge[0]});
    }
  }
  return totalCost;
}

int main() { return 0; }