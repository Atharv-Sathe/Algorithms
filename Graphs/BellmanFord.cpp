#include <iostream>
#include <vector>
using namespace std;


/*
  Given an weighted graph with V vertices numbered from 0 to V-1 and E edges, represented by a 2d array edges[][], 
  where edges[i] = [u, v, w] represents a direct edge from node u to v having w edge weight. You are also given a 
  source vertex src.

  Your task is to compute the shortest distances from the source to all other vertices. If a vertex is 
  unreachable from the source, its distance should be marked as 108. Additionally, if 
  the graph contains a negative weight cycle, return [-1] to indicate that shortest paths cannot be reliably computed.

*/

vector<int> bellmanFord(int V, vector<vector<int>>& edges, int src) {
  vector<int> distances(V, 1e8);
  distances[src] = 0;

  // Perform V iterations of relaxations
  for (int i = 0; i < V; i++) {
    for (auto& edge : edges) {
      int u = edge[0], v = edge[1], wt = edge[2];

      if (distances[u] == 1e8) continue;

      if (distances[v] > distances[u] + wt) {
        // Relax the edges ...
        // However if this is the Vth iteration
        // this suggests a negative wt cycle
        if (i == V - 1) return {-1};

        distances[v] = distances[u] + wt;
      }
    }
  }
  return distances;
}

int main() { return 0; }