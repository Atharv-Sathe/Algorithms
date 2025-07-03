#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

// Path Reconstruction
vector<int> constructPath(vector<int> prev, int src, int dest) {
  vector<int> path;
  int parent = dest;
  path.push_back(parent);
  while(parent != prev[dest]) {
    parent = prev[dest];
    dest = prev[dest];
    path.push_back(parent);
  }
  reverse(path.begin(), path.end());
  return path;
}

// Lazy Dijkstra
/*
  Finds the shortest path cost and path from start to every other node.
*/
pair<vector<int>, vector<int>> dijkstra(int V, vector<vector<int>>& edges, int src) {
  // Build Graph
  vector<vector<pair<int, int>>> adjList(V);
  for (auto& edge : edges) {
    adjList[edge[0]].push_back({edge[1], edge[2]});
    adjList[edge[1]].push_back({edge[0], edge[2]});
  }

  vector<int> prev(V, 0);
  vector<int> distance(V, INT_MAX);
  distance[src] = 0;
  priority_queue<pair<int, int>, vector<pair<int, int>>,
                 greater<pair<int, int>>>
      pq;
  pq.push({0, src});

  vector<bool> visited(V, false);

  while (!pq.empty()) {
    int minDist = pq.top().first;
    int node = pq.top().second;
    pq.pop();

    visited[node] = true;

    for (auto& nbr : adjList[node]) {
      if (visited[nbr.first]) continue;
      int newDist = distance[node] + nbr.second;
      if (newDist < distance[nbr.first]) {
        distance[nbr.first] = newDist;
        pq.push({newDist, nbr.first});
        prev[nbr.first] = node;
      }
    }
  }
  return {distance, prev};
}

// Dijkstra Stopping Early
/*
  Stops the search when the destination node is found.
*/
pair<vector<int>, vector<int>> dijkstra(int V, vector<vector<int>>& edges, int src, int dest) {
  // Build Graph
  vector<vector<pair<int, int>>> adjList(V);
  for (auto& edge : edges) {
    adjList[edge[0]].push_back({edge[1], edge[2]});
    adjList[edge[1]].push_back({edge[0], edge[2]});
  }

  vector<int> prev(V, 0);
  vector<int> distance(V, INT_MAX);
  distance[src] = 0;
  priority_queue<pair<int, int>, vector<pair<int, int>>,
                 greater<pair<int, int>>>
      pq;
  pq.push({0, src});

  vector<bool> visited(V, false);

  while (!pq.empty()) {
    int minDist = pq.top().first;
    int node = pq.top().second;
    pq.pop();

    visited[node] = true;

    if (node == dest) return {distance, prev};
    for (auto& nbr : adjList[node]) {
      if (visited[nbr.first]) continue;
      int newDist = distance[node] + nbr.second;
      if (newDist < distance[nbr.first]) {
        distance[nbr.first] = newDist;
        pq.push({newDist, nbr.first});
        prev[nbr.first] = node;
      }
    }
  }
  return {distance, prev};
}

int main() {
  // Test Case 1: Simple triangle graph
  // 0 --1-- 1
  //  \     /
  //   4   2
  //    \ /
  //     2
  // Shortest path 0->2: 0->1->2 (cost 3)
  vector<vector<int>> edges1 = {{0,1,1},{1,2,2},{0,2,4}};
  auto [dist1, prev1] = dijkstra(3, edges1, 0);
  vector<int> path1 = constructPath(prev1, 0, 2);
  cout << "Test 1: ";
  for(int v : path1) cout << v << " ";
  cout << "\nExpected: 0 1 2\n";
  cout << "Distance: " << dist1[2] << " (Expected: 3)\n\n";

  // Test Case 2: Disconnected graph
  // 0 --1-- 1    2
  // No path from 0 to 2
  vector<vector<int>> edges2 = {{0,1,1}};
  auto [dist2, prev2] = dijkstra(3, edges2, 0);
  cout << "Test 2: ";
  if(dist2[2] == INT_MAX) cout << "No path\n";
  else {
    vector<int> path2 = constructPath(prev2, 0, 2);
    for(int v : path2) cout << v << " ";
  }
  cout << "Expected: No path\n";
  cout << "Distance: " << (dist2[2]==INT_MAX ? -1 : dist2[2]) << " (Expected: -1)\n\n";

  // Test Case 3: Multiple shortest paths
  // 0 --1-- 1 --1-- 2
  //  \           /
  //   ----2------
  // Shortest path 0->2: 0->2 (cost 2) or 0->1->2 (cost 2)
  vector<vector<int>> edges3 = {{0,1,1},{1,2,1},{0,2,2}};
  auto [dist3, prev3] = dijkstra(3, edges3, 0);
  vector<int> path3 = constructPath(prev3, 0, 2);
  cout << "Test 3: ";
  for(int v : path3) cout << v << " ";
  cout << "\nExpected: 0 2 or 0 1 2\n";
  cout << "Distance: " << dist3[2] << " (Expected: 2)\n\n";

  // Test Case 4: Larger graph with cycles
  // 0--1--2
  // |  |  |
  // 4--3--5
  // Shortest path 0->5: 0 1 2 5 (cost 4)
  vector<vector<int>> edges4 = {{0,1,1},{1,2,1},{2,5,2},{5,3,1},{3,4,1},{4,0,2},{1,3,2}};
  auto [dist4, prev4] = dijkstra(6, edges4, 0);
  vector<int> path4 = constructPath(prev4, 0, 5);
  cout << "Test 4: ";
  for(int v : path4) cout << v << " ";
  cout << "\nExpected: 0 1 2 5\n";
  cout << "Distance: " << dist4[5] << " (Expected: 4)\n\n";

  // Test Case 5: Single node graph
  // 0
  // Shortest path 0->0: 0 (cost 0)
  vector<vector<int>> edges5 = {};
  auto [dist5, prev5] = dijkstra(1, edges5, 0);
  vector<int> path5 = constructPath(prev5, 0, 0);
  cout << "Test 5: ";
  for(int v : path5) cout << v << " ";
  cout << "\nExpected: 0\n";
  cout << "Distance: " << dist5[0] << " (Expected: 0)\n";
}

