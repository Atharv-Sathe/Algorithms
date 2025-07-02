#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Performs a depth-first search to compute topological order.
 * 
 * @param loc Current position in the order array to fill.
 * @param order Reference to the array storing topological order.
 * @param adjList Reference to the adjacency list of the graph.
 * @param visited Reference to the visited nodes array.
 * @param i Current node being visited.
 * @return int The next position in the order array to fill.
 * 
 * This function recursively visits all unvisited neighbors of the current node,
 * and assigns the node to the current location in the order array after all its
 * descendants have been processed.
 */
int dfs(int loc, vector<int>& order, vector<vector<int>>& adjList,
  vector<bool>& visited, int i) {
  visited[i] = true; // Mark the current node as visited

  // Visit all unvisited neighbors
  for (int nbr : adjList[i]) {
    if (!visited[nbr]) {
      loc = dfs(loc, order, adjList, visited, nbr);
    }
  }
  order[loc] = i; // Place the node in the topological order
  return loc - 1; // Move to the next position for the next node
}

/**
 * @brief Computes the topological sort of a directed acyclic graph (DAG).
 * 
 * @param adjList Reference to the adjacency list of the graph.
 * @return vector<int> The topological order of nodes.
 * 
 * This function initializes the visited and order arrays, and calls DFS
 * for each unvisited node to fill the topological order.
 * 
 * Time Complexity: O(V + E)
 * Space Complexity: O(V)
 */
vector<int> toposort(vector<vector<int>>& adjList) {
  int nodeCount = adjList.size();
  vector<bool> visited(nodeCount, false); // Track visited nodes
  vector<int> order(nodeCount, 0);        // Store topological order
  int loc = nodeCount - 1;                // Start filling order from the end
  for (int i = 0; i < nodeCount; i++) {
    if (!visited[i]) {
      loc = dfs(loc, order, adjList, visited, i);
    }
  }
  return order;
}

int main() {
  // Create adjacency list for the graph with 13 nodes (A-M)
  std::vector<std::vector<int>> adjList(13);

  // Define edges: each index represents a node (0 = A, 1 = B, ..., 12 = M)
  adjList[0] = {3};        // A -> D
  adjList[1] = {6};        // B -> G
  adjList[2] = {0, 1};     // C -> A, B
  adjList[3] = {7, 6, 8};  // D -> H, G, I
  adjList[4] = {0, 3, 5};  // E -> A, D, F
  adjList[5] = {9};        // F -> J
  adjList[6] = {8};        // G -> I
  adjList[7] = {8};        // H -> I
  adjList[8] = {11};       // I -> L
  adjList[9] = {11, 12};   // J -> L, M
  adjList[10] = {9};       // K -> J
  adjList[11] = {};        // L -> (no outgoing edges)
  adjList[12] = {};        // M -> (no outgoing edges)

  // Compute topological order
  vector<int> order = toposort(adjList);

  // Print topological order as letters (A-M)
  for (int i : order) {
    cout << (char)(i + 65) << " ";
  }
  cout << endl;

  // Print topological order as indices
  for (int i : order) {
    cout << i << " " ;
  }
  cout << endl;

  return 0;
}