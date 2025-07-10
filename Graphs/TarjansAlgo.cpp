#include <iostream>
#include <vector>
using namespace std;

/*
  There are n servers numbered from 0 to n - 1 connected by undirected server-to-server 
  connections forming a network where connections[i] = [ai, bi] represents a connection 
  between servers ai and bi. Any server can reach other servers directly or indirectly 
  through the network.

  A critical connection is a connection that, if removed, will make some servers unable 
  to reach some other server.

  Return all critical connections in the network in any order.
*/


// Tarjan's Algo to print all SCC
void dfs(vector<vector<int>>& adjList, int node, vector<bool>& visited,
         vector<int>& disc, vector<int>& low, int parent,
         vector<vector<int>>& result, int& time) {
  visited[node] = true;
  disc[node] = low[node] = time++;
  for (int nbr : adjList[node]) {
    if (nbr == parent) continue;

    if (!visited[nbr]) {
      dfs(adjList, nbr, visited, disc, low, node, result, time);
      low[node] = min(low[node], low[nbr]);

      // Check if this edge is bridge or not
      if (low[nbr] > disc[node]) result.push_back({node, nbr});
    } else {
      // Nbr is already visited and is not parent
      // This must be a backedge
      low[node] = min(low[node], disc[nbr]);
    }
  }
}

vector<vector<int>> criticalConnections(int n,
                                        vector<vector<int>>& connections) {
  // Creating an adjList
  vector<vector<int>> adjList(n);
  for (auto& connection : connections) {
    adjList[connection[0]].push_back(connection[1]);
    adjList[connection[1]].push_back(connection[0]);
  }

  // Required data structures
  vector<bool> visited(n, false);
  vector<int> disc(n, -1);  // Discovery Time
  vector<int> low(n, -1);   // Lowest Discovery Time Possible
  int parent = -1;
  vector<vector<int>> result;

  for (int i = 0; i < n; i++) {
    if (!visited[i]) {
      int time = 0;
      for (int i = 0; i < n; i++) {
        if (!visited[i]) {
          dfs(adjList, i, visited, disc, low, parent, result, time);
        }
      }
    }
  }
}

int main() { return 0; }