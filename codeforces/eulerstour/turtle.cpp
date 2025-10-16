#include <bits/stdc++.h>
using namespace std;

vector<int> primes;

void sieve(int limit = 300000) {
    vector<bool> isPrime(limit + 1, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i * i <= limit; i++) {
        if (isPrime[i])
            for (int j = i * i; j <= limit; j += i)
                isPrime[j] = false;
    }
    for (int i = 2; i <= limit; i++)
        if (isPrime[i]) primes.push_back(i);
}

long long L(long long m) {
    if (m % 2) return m * (m + 1) / 2;
    else return m * m / 2 + 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    sieve();

    int T;
    cin >> T;
    while (T--) {
        long long n;
        cin >> n;

        // 1. Find smallest m s.t. L(m) >= n-1
        int m = 1;
        while (L(m) < n - 1) m++;

        // 2. Build adjacency for K_m* (with self loops)
        vector<vector<pair<int,int>>> g(m + 1);
        int edgeId = 0;
        for (int i = 1; i <= m; i++) {
            for (int j = i; j <= m; j++) {
                g[i].push_back({j, edgeId});
                if (i != j) g[j].push_back({i, edgeId});
                edgeId++;
            }
        }

        // If m even, remove (2,3),(4,5),... edges
        if (m % 2 == 0) {
            for (int i = 2; i + 1 <= m; i += 2) {
                // remove edge (i, i+1)
                for (auto it = g[i].begin(); it != g[i].end(); it++) {
                    if (it->first == i + 1) {
                        g[i].erase(it);
                        break;
                    }
                }
                for (auto it = g[i + 1].begin(); it != g[i + 1].end(); it++) {
                    if (it->first == i) {
                        g[i + 1].erase(it);
                        break;
                    }
                }
            }
        }

        vector<int> ans;
        vector<int> used(edgeId, 0);

        // 3. Hierholzer’s algorithm for Eulerian trail
        function<void(int)> dfs = [&](int u) {
            while (!g[u].empty()) {
                auto [v, id] = g[u].back();
                g[u].pop_back();
                if (used[id]) continue;
                used[id] = 1;
                dfs(v);
            }
            ans.push_back(u);
        };
        dfs(1);
        reverse(ans.begin(), ans.end());

        // 4. Output first n vertices mapped to primes
        cout << fixed;
        for (int i = 0; i < n; i++) {
            cout << primes[ans[i] - 1] << (i + 1 == n ? '\n' : ' ');
        }
    }
}


// wealurlwe rdiscsit erer