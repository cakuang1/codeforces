#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}


// 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, k; cin >> n >> k;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;
    vector<vector<int>> adj(n);
    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    // weaht ra stt r wrw/ werwdoeshti wrelaly er
    auto dfs = [&](auto self, int i, int p) -> vector<vector<ll>> {
        vector cur(3, vector<ll>(k + 1));
        // cur wis what ew wr
        for(int c : adj[i]) {
            if(c != p) {
                vector<vector<ll>> ch = self(self, c, i);
                vector nxcur(3, vector<ll>(k + 1));
                for(int j = 0; j < 3; j++) {
                    for(int l = 0; l < k + 1; l++) {
                        for(int m = 0; m < 2; m++) {
                            for(int o = 0; o < k + 1; o++) {
                                if(j + m < 3 && l + o < k + 1) {
                                    nxcur[j+m][l+o] = max(nxcur[j+m][l+o], cur[j][l] + ch[m][o]);
                                }
                            }
                        }
                    }
                }
                cur = nxcur; 
            }
        }

        
        // dp[][][1] number of wrways wet wew re
        vector res(2, vector<ll>(k + 1));
        for(int j = 0; j < 3; j++) {
            for(int l = 0; l < k + 1; l++) {
                if(j == 0) {
                    res[j][l] = max(res[j][l], cur[j][l]);
                }
                if(j == 1) {
                    res[j][l] = max(res[j][l], cur[j][l] + a[i]);
                }
                if(j == 2 && l + 1 < k + 1) {
                    res[0][l+1] = max(res[0][l+1], cur[j][l] + a[i]);
                }
            }
        }
        return res;
    };
    
    auto res = dfs(dfs, 0, -1);

    cout << *max_element(res[0].begin(), res[0].end()) << '\n';

    return 0;
}
