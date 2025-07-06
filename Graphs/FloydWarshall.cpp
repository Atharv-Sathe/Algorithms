#include <iostream>
#include <vector>
using namespace std;

/*
You are given an weighted directed graph, represented by an adjacency matrix, 
dist[][] of size n x n, where dist[i][j] represents the weight of the edge from 
node i to node j. If there is no direct edge, dist[i][j] is set to a large value 
(i.e., 108) to represent infinity.
The graph may contain negative edge weights, but it does not contain any negative 
weight cycles.

Your task is to find the shortest distance between every pair of nodes i and j 
in the graph.

Note: Modify the distances for every pair in place.
*/

vector<vector<int>> floydWarshall(vector<vector<int>> &dist) {
  int n = dist.size();

  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (dist[i][k] == 1e8 || dist[k][j] == 1e8) continue;

        if (dist[i][j] > dist[i][k] + dist[k][j]) {
          dist[i][j] = dist[i][k] + dist[k][j];
        }
      }
    }
  }

  //  If there is any negative weight cycle the algorithm will be
  // able to find a way from a node to itself in negative distance
  // this proves that there is an existence of a negative edge wt cycle
  for (int i = 0; i < n; i++) {
    if (dist[i][i] < 0) return {{-1}};
  }
}

int main() { return 0; }