#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<ll>> d(n+1, vector<ll>(n+1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> d[i][j];
        }
    }

    // compute initial sum over unordered pairs i<j
    ll sum = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i+1; j <= n; j++) {
            sum += d[i][j];
        }
    }

    int k;
    cin >> k;
    while (k--) {
        int a, b;
        ll c;
        cin >> a >> b >> c;

        // if this new road is not better than existing shortest path, no change
        if (c < d[a][b]) {
            // try to improve all pairs i<j
            for (int i = 1; i <= n; i++) {
                for (int j = i+1; j <= n; j++) {
                    // consider paths i→a→b→j and i→b→a→j
                    ll viaAB = d[i][a] + c + d[b][j];
                    ll viaBA = d[i][b] + c + d[a][j];
                    ll best = min(d[i][j], min(viaAB, viaBA));
                    if (best < d[i][j]) {
                        sum -= (d[i][j] - best);
                        d[i][j] = d[j][i] = best;
                    }
                }
            }
        }

        cout << sum << " ";
    }
    cout << "\n";
    return 0;
}
