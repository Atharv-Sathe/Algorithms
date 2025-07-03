#include <iostream>
#include <vector>
using namespace std;

// Single Source Longest Path in DAG

int dfs(vector<vector<pair<int, int>>>& adjList, int i, vector<bool>& visited,
        int loc, vector<int>& order) {
  visited[i] = true;

  for (auto& nbr : adjList[i]) {
    if (!visited[nbr.first]) {
      loc = dfs(adjList, nbr.first, visited, loc, order);
    }
  }

  order[loc] = i;
  return loc - 1;
}

vector<int> topoSort(vector<vector<pair<int, int>>>& adjList) {
  int nodeCount = adjList.size();

  vector<int> order(nodeCount, 0);
  vector<bool> visited(nodeCount, false);

  int loc = nodeCount - 1;
  for (int i = 0; i < nodeCount; i++) {
    if (!visited[i]) {
      loc = dfs(adjList, i, visited, loc, order);
    }
  }

  return order;
}

vector<int> shortestPath(int V, int E, vector<vector<int>>& edges, int start) {
  // Build Graph
  // Push negative edge weights
  vector<vector<pair<int, int>>> adjList(V);
  for (auto& edge : edges) {
    adjList[edge[0]].push_back({edge[1], -edge[2]});
  }

  vector<int> order = topoSort(adjList);

  vector<int> distance(V, INT_MAX);
  distance[start] = 0;

  for (int i = 0; i < V; i++) {
    int node = order[i];
    if (distance[node] == INT_MAX) continue;

    for (auto& nbr : adjList[node]) {
      distance[nbr.first] =
          min(distance[nbr.first], distance[node] + nbr.second);
    }
  }

  // Multiply -1 back to distances
  for (int& i : distance) i *= -1;
  return distance;
}

int main() { return 0; }