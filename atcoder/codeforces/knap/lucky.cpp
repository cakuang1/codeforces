#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> parent, sz;
    DSU(int n) {
        parent.resize(n+1);
        sz.assign(n+1, 1);
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }
    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a != b) {
            if (sz[a] < sz[b]) swap(a,b);
            parent[b] = a;
            sz[a] += sz[b];
        }
    }
    int size(int x) {
        return sz[find(x)];
    }
};

vector<int> luckyNumbers(int n) {
    vector<int> res;
    function<void(long long)> dfs = [&](long long cur) {
        if (cur > n) return;
        if (cur > 0) res.push_back((int)cur);
        dfs(cur * 10 + 4);
        dfs(cur * 10 + 7);
    };
    dfs(0);
    sort(res.begin(), res.end());
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    DSU dsu(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        dsu.unite(u, v);
    }

    // collect component sizes
    unordered_map<int,int> compSize;
    for (int i = 1; i <= n; i++) {
        compSize[dsu.find(i)] = dsu.size(i);
    }

    // count frequencies of sizes
    unordered_map<int,int> freq;
    for (auto &p : compSize) {
        freq[p.second]++;
    }

    // subset-sum style DP: dp[s] = min number of components used to make sum s
    vector<int> dp(n+1, INT_MAX);
    dp[0] = 0;

    for (auto [sz, occ] : freq) {
        // binary splitting of multiplicity
        vector<int> eff;
        int curr = 1;
        while (occ >= curr) {
            eff.push_back(sz * curr);
            occ -= curr;
            curr <<= 1;
        }
        
        if (occ > 0) eff.push_back(sz * occ);
        for (int w : eff) {
            int cnt = w / sz; // number of components represented
            for (int j = n; j >= w; j--) {
                if (dp[j-w] != INT_MAX) {
                    dp[j] = min(dp[j], dp[j-w] + cnt);
                }
            }
        }
    }  
    // doesth isealtl wwork w=ra we
    // weconvulaitwr son ar wear e 
    //  wdeos htis ework weandwrhow o attmpy ethis? wew  w
    
    // wdoesthi werel ww r
    // res[i] = a[k] + b[j] for all k + j  = i;
     
    // its eabckawayds wewhy ww  w
    
    // wconvulait weinswdefine w for weall i w

    // wdoes it rmatch the apttern w we
    // parentetn weamtvhcing wrusing we werwid erlcard w
    // pattenr ammtchi nw er
    // doest is male ense we
    // classoc wereducw
    // res[i] = f[k] *
    // the sum we 
    // multiply wrvalueswe
    // [1,0,1,1];
    // [1,0,1,1];
    // wewahtswhte wxpectedmathc wrw
    // detemrin eall weapirswr w w
    // g[i] = the number w w
    // ordered wpairs r
    vector<int> lucky = luckyNumbers(n);

    int ans = INT_MAX;
    for (int L : lucky) {
        if (L <= n && dp[L] != INT_MAX) {
            ans = min(ans, dp[L] - 1);
        }
    }


    if (ans == INT_MAX) cout << -1 << "\n";
    else cout << ans << "\n";

    return 0;
}
