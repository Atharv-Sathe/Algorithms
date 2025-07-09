#include <iostream>
#include <stack>
#include <vector>
using namespace std;

/*
  Given an adjacency list, adj of Directed Graph, Find the number of strongly
  connected components in the graph.
*/

void dfs(vector<vector<int>>& adj, int i, vector<bool>& visited,
         stack<int>& order) {
  visited[i] = true;

  for (int nbr : adj[i]) {
    if (!visited[nbr]) {
      dfs(adj, nbr, visited, order);
    }
  }

  order.push(i);
}

void dfs(vector<vector<int>>& adj, int i, vector<bool>& visited) {
  visited[i] = true;

  for (int nbr : adj[i]) {
    if (!visited[nbr]) {
      dfs(adj, nbr, visited);
    }
  }
}

int kosaraju(vector<vector<int>>& adj) {
  /*
Why the two-pass DFS with a stack?

1.  The first DFS on the original graph processes nodes in a "post-order." The
last node to finish (and be pushed to the stack) is guaranteed to be in a
"source" SCC—a component with no outgoing edges to other SCCs.

2.  When we reverse the graph, this "source" SCC becomes a "sink" SCC, meaning
it has no outgoing edges in the reversed graph.

3.  By starting the second DFS from the top of the stack, we are guaranteed to
start in one of these sink SCCs. This "traps" the DFS, forcing it to visit every
node within that component and *only* that component before it finishes. This
allows us to correctly identify and count one SCC at a time. A standard
ascending order would risk starting in a component that could "leak" into
another during traversal, leading to an incorrect result.
*/

  // Do a DFS
  stack<int> order;
  int n = adj.size();

  vector<bool> visited(n, false);

  for (int i = 0; i < n; i++) {
    if (!visited[i]) {
      dfs(adj, i, visited, order);
    }
  }

  vector<vector<int>> reverseGraph(n);

  // Reverse the edges
  for (int i = 0; i < n; i++) {
    for (int j : adj[i]) {
      reverseGraph[j].push_back(i);
    }
  }

  int sccCount = 0;

  vector<bool> seen(n, false);

  while (!order.empty()) {
    int node = order.top();
    order.pop();

    if (!seen[node]) {
      sccCount++;
      dfs(reverseGraph, node, seen);
    }
  }

  return sccCount;
}

int main() { return 0; }