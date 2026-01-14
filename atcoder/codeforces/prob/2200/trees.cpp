#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
vector<int> tree[MAXN];
int depth[MAXN];

void dfs(int node, int parent) {
    for (int neighbor : tree[node]) {
        if (neighbor != parent) {
            depth[neighbor] = depth[node] + 1;
            dfs(neighbor, node);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    // Read tree edges
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    // Compute depths using DFS
    depth[1] = 0; // Root node
    dfs(1, -1);

    // Calculate the expectation
    double expectation = 0.0;
    for (int i = 1; i <= n; i++) {
        expectation += 1.0 / (depth[i] + 1);
    }

    cout << fixed << setprecision(6) << expectation << endl;
    // sum wer
    return 0;
}
