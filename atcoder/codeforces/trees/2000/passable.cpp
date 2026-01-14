#include <bits/stdc++.h>

#define int long long
#define pb emplace_back
#define mp make_pair
#define x first
#define y second
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()

typedef long double ld;
typedef long long ll;

using namespace std;

mt19937 rnd(143);

const int inf = 1e15;
const int M = 1e9 + 7;
const ld pi = atan2(0, -1);
const ld eps = 1e-6;

int n, sz;
vector<vector<int>> sl, up;
vector<int> d;

void precalc(int v, int p){
    d[v] = d[p] + 1;
    up[v][0] = p;
    for(int i = 1; i <= sz; ++i){
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    for(int u: sl[v]){
        if(u == p) continue;
        precalc(u, v);
    }
}

int lca(int u, int v){
    if(d[u] < d[v]){
        swap(u, v);
    }
    for(int cur = sz; cur >= 0; --cur){
        if (d[u] - (1 << cur) >= d[v]) {
            u = up[u][cur];
        }
    }
    for(int cur = sz; cur >= 0; --cur){
        if (up[u][cur] != up[v][cur]) {
            u = up[u][cur];
            v = up[v][cur];
        }
    }
    return u == v ? u : up[u][0];
}

void solve(){
    cin >> n;
    sz = 0;
    while ((1 << sz) < n) sz++;
    d.assign(n, -1);
    up.assign(n, vector<int>(sz + 1));
    sl.assign(n, vector<int>(0));
    for(int i = 1; i < n; ++i){
        int u, v;
        cin >> u >> v;
        sl[--u].push_back(--v);
        sl[v].push_back(u);
    }
    precalc(0, 0);
    int q;
    cin >> q;
    for(; q; --q){
        int k;
        cin >> k;
        vector<int> p(k);
        for(int &e: p) {
            cin >> e;
            --e;
        }
        sort(all(p), [](int a, int b) {
            return d[a] > d[b];
        });
        vector<bool> used(k);
        for(int i = 0; i < k; ++i){
            if(lca(p[0], p[i]) == p[i]) used[i] = true;
        }
        int f = 0;
        while (f < k && used[f]) f++;
        if(f == k){
            cout << "YES\n";
            continue;
        }
        bool ans = true;
        for(int i = f; i < k; ++i){
            if(lca(p[f], p[i]) == p[i]) used[i] = true;
        }
        for(bool e: used){
            ans &= e;
        }
        ans &= d[lca(p[0], p[f])] <= d[p.back()];
        if(ans) cout << "YES\n";
        else cout << "NO\n";
    }
}

bool multi = false;

signed main() {
    int t = 1;
    if (multi)cin >> t;
    for (; t; --t) {
        solve();
        //cout << endl;
    }
    return 0;
}