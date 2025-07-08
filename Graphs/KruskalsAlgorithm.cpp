#include <iostream>
#include <numeric>
#include <queue>
#include <vector>
using namespace std;

int find(int n, vector<int>& par) {
  int root = n;
  while (root != par[root]) {
    root = par[root];
  }

  // Path Compression
  while (n != par[root]) {
    int next = par[n];
    par[n] = root;
    n = next;
  }

  return root;
}

void connect(int n1, int n2, vector<int>& size, vector<int>& parent) {
  int root1 = find(n1, parent);
  int root2 = find(n2, parent);

  if (size[root1] < size[root2]) {
    size[root2] += size[root1];
    parent[root1] = root2;
  } else {
    size[root1] += size[root2];
    parent[root2] = root1;
  }
}

int kruskalsMST(int V, vector<vector<int>>& edges) {
  vector<int> par(V);
  iota(par.begin(), par.end(), 0);
  vector<int> size(V, 1);

  priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
  for (auto& edge : edges) pq.push({edge[2], edge[0], edge[1]});

  int mstCost = 0;
  int edgeCount = 0;
  while (!pq.empty() && edgeCount < V - 1) {
    int wt = pq.top()[0], n1 = pq.top()[1], n2 = pq.top()[2];
    pq.pop();

    // Skip including this edge if n1 and n2 are already joined
    if (find(n1, par) == find(n2, par)) continue;

    mstCost += wt;
    edgeCount++;
    connect(n1, n2, size, par);
  }
  return mstCost;
}

int main() { return 0; }