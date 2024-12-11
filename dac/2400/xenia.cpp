#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
const int MAXN = 100005;

vector<int> tree[MAXN];
vector<pair<int, int>> ancestors[MAXN]; // {centroid, distance}
bool isCentroid[MAXN];
int subtreeSize[MAXN];
int minDist[MAXN];

// Calculate the size of each subtree
void calculateSubtreeSize(int node, int parent) {
    subtreeSize[node] = 1;
    for (int neighbor : tree[node]) {
        if (neighbor != parent && !isCentroid[neighbor]) {
            calculateSubtreeSize(neighbor, node);
            subtreeSize[node] += subtreeSize[neighbor];
        }
    }
}

// Find the centroid of a subtree
int findCentroid(int node, int parent, int totalSize) {
    for (int neighbor : tree[node]) {
        if (neighbor != parent && !isCentroid[neighbor] && subtreeSize[neighbor] > totalSize / 2) {
            return findCentroid(neighbor, node, totalSize);
        }
    }
    return node;
}

// Calculate distances and populate ancestors
void calculateDistances(int node, int centroid, int parent, int dist) {
    ancestors[node].push_back({centroid, dist});
    for (int neighbor : tree[node]) {
        if (neighbor != parent && !isCentroid[neighbor]) {
            calculateDistances(neighbor, centroid, node, dist + 1);
        }
    }
}

// Decompose the tree into a Centroid Tree
void decomposeTree(int node) {
    calculateSubtreeSize(node, -1);
    int centroid = findCentroid(node, -1, subtreeSize[node]);

    // Mark the centroid and calculate distances
    isCentroid[centroid] = true;
    calculateDistances(centroid, centroid, -1, 0);

    // Recurse on the remaining subtrees
    for (int neighbor : tree[centroid]) {
        if (!isCentroid[neighbor]) {
            decomposeTree(neighbor);
        }
    }
}

// Paint a node red and update distances
void paint(int node) {
    for (auto &[centroid, dist] : ancestors[node]) {
        minDist[centroid] = min(minDist[centroid], dist);
    }
}

// Query the shortest distance to any red node
int query(int node) {
    int res = INF;
    for (auto &[centroid, dist] : ancestors[node]) {
        res = min(res, dist + minDist[centroid]);
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    // Input the tree
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    // Initialize
    fill(minDist, minDist + n + 1, INF);

    // Build the Centroid Tree
    decomposeTree(1);

    // Paint node 1 red
    paint(1);

    // Process queries
    while (m--) {
        int type, v;
        cin >> type >> v;
        if (type == 1) {
            paint(v); // Paint node red
        } else {
            cout << query(v) << "\n"; // Query shortest distance to a red node
        }
    }

    return 0;
}

// ciel the commander e