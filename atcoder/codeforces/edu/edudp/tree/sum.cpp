#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll INF = 1e18;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> parent(n + 1, 0);
    vector<vector<int>> tree(n + 1);
    vector<ll> s(n + 1);
    vector<ll> a(n + 1, 0);

    // Read parent array and construct tree
    for (int i = 2; i <= n; i++) {
        cin >> parent[i];
        tree[parent[i]].push_back(i);
    }

    // Read s values
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
    }

    // BFS to process tree level by level
    queue<int> q;
    q.push(1);
    
    ll totalSum = 0;
    
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        
        // If node is root, a[1] = s[1]
        if (node == 1) {
            a[1] = s[1];
            totalSum += a[1];
        } else {
            int parentNode = parent[node];

            // If s[node] is -1 (erased value), reconstruct it as the minimum valid sum
            if (s[node] == -1) {
                if (tree[node].empty()) {
                    // If node is a leaf, we should never have s[node] = -1, so it's an error
                    s[node] = s[parentNode]; // Just keep same as parent
                } else {
                    ll minChildS = INF;
                    for (int child : tree[node]) {
                        minChildS = min(minChildS, s[child]);
                    }
                    s[node] = minChildS;
                }
            }

            // Compute a[node] using a_v = s_v - s_parent
            a[node] = s[node] - s[parentNode];
            if (a[node] < 0) {
                cout << -1 << endl;
                return 0;
            }

            totalSum += a[node];
        }

        // Push children into the queue
        for (int child : tree[node]) {
            q.push(child);
        }
    }

    cout << totalSum << endl;
    return 0;
}
