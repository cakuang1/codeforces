#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    // Read adjacency matrix into dist
    vector<vector<ll>> dist(n+1, vector<ll>(n+1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> dist[i][j];
        }
    }

    // Read deletion order and build reverse addition order
    vector<int> x(n+1), add(n+1);
    for (int i = 1; i <= n; i++) {
        cin >> x[i];
    }
    for (int i = 1; i <= n; i++) {
        add[i] = x[n - i + 1];
    }

    vector<bool> used(n+1, false);
    vector<ll> ans(n+1);

    // Reverse process: add vertices one by one
    for (int k = 1; k <= n; k++) {
        int w = add[k];
        used[w] = true;

        // Floyd–Warshall relaxation allowing w as an intermediate
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                ll via_w = dist[i][w] + dist[w][j];
                if (via_w < dist[i][j]) {
                    dist[i][j] = via_w;
                }
            }
        }

        // Sum shortest paths over all active vertices
        ll sum = 0;
        for (int i = 1; i <= n; i++) if (used[i]) {
            for (int j = 1; j <= n; j++) if (used[j]) {
                sum += dist[i][j];
            }
        }
        ans[k] = sum;
    }

    // Output answers in the order before each deletion
    // (i.e., reverse of the addition order)
    for (int k = n; k >= 1; k--) {
        cout << ans[k] << (k > 1 ? ' ' : '\n');
    }

    return 0;
}

