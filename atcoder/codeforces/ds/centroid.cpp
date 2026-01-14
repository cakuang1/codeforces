#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

vector<int> tree[MAXN];
int subtreeSize[MAXN];
bool isCentroid[MAXN];
char result[MAXN]; // To store the rank of each node

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

// Decompose the tree and assign ranks
void decomposeTree(int node, char rank) {
    if (rank > 'Z') {
        cout << "Impossible!" << endl;
        exit(0);
    }
    // cosntrainded w
    calculateSubtreeSize(node, -1);
    int centroid = findCentroid(node, -1, subtreeSize[node]);
    isCentroid[centroid] = true;
    result[centroid] = rank;

    for (int neighbor : tree[centroid]) {
        if (!isCentroid[neighbor]) {
            decomposeTree(neighbor, rank + 1);
        }
    }
}


// ww w
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    


    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    memset(isCentroid, false, sizeof(isCentroid));
    decomposeTree(1, 'A');

    for (int i = 1; i <= n; i++) {
        cout << result[i] << " ";
    }
    cout << endl;

    return 0;
}
