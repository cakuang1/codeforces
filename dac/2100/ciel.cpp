#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
vector<int> tree[MAXN];  // Adjacency list for the tree
bool isCentroid[MAXN];   // Marks if a node is a centroid
int subtreeSize[MAXN];   // Stores the size of the subtree for each node
int parentCentroid[MAXN]; // Stores the parent of the node in the centroid tree

// Function to calculate the size of each subtree
void calculateSubtreeSize(int node, int parent) {
    subtreeSize[node] = 1;
    for (int neighbor : tree[node]) {
        if (neighbor != parent && !isCentroid[neighbor]) {
            calculateSubtreeSize(neighbor, node);
            subtreeSize[node] += subtreeSize[neighbor];
        }
    }
}

// Function to find the centroid of a tree/subtree
int findCentroid(int node, int parent, int totalSize) {
    for (int neighbor : tree[node]) {
        if (neighbor != parent && !isCentroid[neighbor] && subtreeSize[neighbor] > totalSize / 2) {
            return findCentroid(neighbor, node, totalSize);
        }
    }
    return node;
}

// Function to decompose the tree
void decomposeTree(int node, int parent) {
    // Calculate the size of the current subtree
    calculateSubtreeSize(node, -1);

    // Find the centroid of the subtree
    int centroid = findCentroid(node, -1, subtreeSize[node]);

    // Mark the centroid
    isCentroid[centroid] = true;
    parentCentroid[centroid] = parent;

    // Decompose each subtree of the centroid
    for (int neighbor : tree[centroid]) {
        if (!isCentroid[neighbor]) {
            decomposeTree(neighbor, centroid);
        }
    }
}

// Example usage
int main() {
    int n; // Number of nodes
    cin >> n;

    // Input the tree
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    // Initialize arrays
    memset(isCentroid, false, sizeof(isCentroid));
    memset(parentCentroid, -1, sizeof(parentCentroid));

    decomposeTree(1, -1); // Assuming the tree is rooted at node 1

    // Output the centroid tree
    cout << "Centroid Tree Parent Mapping:" << endl;
    for (int i = 1; i <= n; i++) {
        cout << "Node " << i << " -> Parent Centroid: " << parentCentroid[i] << endl;
    }

    return 0;
}


 // what does htis wmean  er w
 // w 