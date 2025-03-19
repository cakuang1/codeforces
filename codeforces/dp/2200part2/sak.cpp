#include <bits/stdc++.h>
 
//#define int long long
#define pb emplace_back
#define mp make_pair
#define x first
#define y second
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
 
typedef long double ld;
typedef long long ll;
 
using namespace std;
 
mt19937 rnd(time(nullptr));
 
const int inf = 1e9;
const int M = 1e9 + 7;
const ld pi = atan2(0, -1);
const ld eps = 1e-6;
 
void precalc(int v, int p, vector<vector<int>> &sl, vector<pair<int, int>> &maxd, vector<int> &h){
    maxd[v] = {0, 0};
    if (v != p) h[v] = h[p] + 1;
    for(int u: sl[v]){
        if (u == p) continue;
        precalc(u, v, sl, maxd, h);
        if (maxd[v].y < maxd[u].x + 1) {
            maxd[v].y = maxd[u].x + 1;
        }
        if (maxd[v].y > maxd[v].x) {
            swap(maxd[v].x, maxd[v].y);
        }
    }
}
 
void calc_binups(int v, int p, vector<vector<int>> &sl, vector<vector<pair<int, int>>> &binup, vector<pair<int, int>> &maxd, vector<int> &h){
    binup[v][0] = {maxd[p].x, p};
    if (maxd[p].x == maxd[v].x + 1) {
        binup[v][0].x = maxd[p].y;
    }
    binup[v][0].x -= h[p];
    for(int i = 1; i < 20; ++i){
        binup[v][i].y = binup[binup[v][i - 1].y][i - 1].y;
        binup[v][i].x = max(binup[v][i - 1].x, binup[binup[v][i - 1].y][i - 1].x);
    }
 
    for(int u: sl[v]){
        if (u == p) continue;
        calc_binups(u, v, sl, binup, maxd, h);
    }
}
 
int get_ans(int v, int k, vector<vector<pair<int, int>>> &binup, vector<pair<int, int>> &maxd, vector<int> &h){
    k = min(k, h[v]);
    int res = maxd[v].x - h[v];
    int ini = h[v];
    for(int i = 19; i >= 0; --i){
        if ((1 << i) <= k) {
            res = max(res, binup[v][i].x);
            v = binup[v][i].y;
            k -= (1 << i);
        }
    }
    return res + ini;
}
 
void solve(int tc){
    int n;
    cin >> n;
    vector<vector<int>> sl(n);
    for(int i = 1; i < n; ++i){
        int u, v;
        cin >> u >> v;
        sl[--u].emplace_back(--v);
        sl[v].emplace_back(u);
    }
    vector<pair<int, int>> maxd(n);
    vector<int> h(n);
    precalc(0, 0, sl, maxd, h);
    vector<vector<pair<int, int>>> binup(n, vector<pair<int, int>>(20));
    calc_binups(0, 0, sl, binup, maxd, h);
    int q;
    cin >> q;
    for(int _ = 0; _ < q; ++_){
        int v, k;
        cin >> v >> k;
        cout << get_ans(v - 1, k, binup, maxd, h) << " ";
    }
}
 
bool multi = true;
 
signed main() {
    int t = 1;
    if (multi)cin >> t;
    for (int i = 1; i <= t; ++i) {
        solve(i);
        cout << "\n";
    }
    return 0;
}



