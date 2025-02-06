#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll mod = 1e9 + 7; // Default modulo
const ll mod2 = 998244353; 
const int N = 2e5 + 10; // Adjust size as needed
const ll p = 31;        // Base for hashing

// Union-Find structures
vector<int> p; // Parent array
vector<int> r; // Rank array

// Find with path compression
int find(int a) {
    if (a == p[a]) {
        return a;
    }
    return p[a] = find(p[a]);   
}

// Union by rank
void unionSets(int a, int b) {
    int p1 = find(a);
    int p2 = find(b);

    if (p1 != p2) {
        if (r[p1] < r[p2]) { 
            swap(p1, p2); 
        }
        p[p2] = p1; // Make p1 the parent
        r[p1] += r[p2]; // Update the rank
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    ll n;
    cin >> n;

    // Initialize Union-Find
    p.resize(2 * n + 1);
    r.resize(2 * n + 1); 
    for (int i = 0; i < 2 * n + 1; i++) {
        p[i] = i;
        r[i] = 1;
    }

    // Adjacency list to store the tree structure
    vector<vector<int>> adj(2 * n + 1);

    int currnode = n; // Start assigning supernodes after the original nodes
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--; // Convert to 0-based indexing

        int p1 = find(u);
        int p2 = find(v);
        int size1 = r[p1];
        int size2 = r[p2];

        // Create a supernode for the union
        adj[currnode].push_back(p1);
        adj[currnode].push_back(p2);
        adj[p1].push_back(currnode);
        adj[p2].push_back(currnode);

        // Merge components and update ranks
        unionSets(p1, currnode);
        unionSets(p2, currnode);
        r[currnode] = size1 + size2;

        currnode++;
    }

    // Result vector to store the answer for each node
    vector<ll> res(n, 0);

    // DFS to calculate the result
    function<void(int, int, ll)> dfs = [&](int node, int parent, ll depth) {
        if (node < n) { // If this is a leaf node (original node)
            res[node] = depth;
        }
        for (int neighbor : adj[node]) {
            if (neighbor != parent) {
                dfs(neighbor, node, depth + 1);
            }
        }
    };

    // Start DFS from the root (last supernode created)
    dfs(currnode - 1, -1, 0);

    // Output the results
    for (ll v : res) {
        cout << v << " ";
    }
    cout << endl;

    return 0;
}
