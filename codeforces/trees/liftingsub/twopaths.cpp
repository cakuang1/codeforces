#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
struct info {
    int sum, minPrefL, maxPrefL, minPrefR, maxPrefR, minSeg, maxSeg;
 
    info(int el = 0) {
        sum = el;
        minSeg = minPrefL = minPrefR = min(el, 0);
        maxSeg = maxPrefL = maxPrefR = max(el, 0);
    }
};
 
struct question {
    int u, v, x;
};
 
info merge(info& a, info& b) {
    info res;
    res.sum = a.sum + b.sum;
    res.minPrefL = min(a.minPrefL, a.sum + b.minPrefL);
    res.maxPrefL = max(a.maxPrefL, a.sum + b.maxPrefL);
    res.minPrefR = min(a.minPrefR + b.sum, b.minPrefR);
    res.maxPrefR = max(a.maxPrefR + b.sum, b.maxPrefR);
    res.minSeg = min({a.minSeg, b.minSeg, a.minPrefR + b.minPrefL});
    res.maxSeg = max({a.maxSeg, b.maxSeg, a.maxPrefR + b.maxPrefL});
    return res;
}
 
const int MAXN = 200100;
const int lg = 17;
 
int up[lg + 1][MAXN];
info ans[lg + 1][MAXN];
int d[MAXN];
 
void solve() {
    int n;
    cin >> n;
 
    for (int i = 0; i <= lg; i++) up[i][0] = 0;
    ans[0][0] = info(1);
    d[0] = 0;
 
    int cur = 0;
    for (int q = 0; q < n; q++) {
        char c;
        cin >> c;
        if (c == '+') {
            int v, x;
            cin >> v >> x;
            v--;
            cur++;
 
            d[cur] = d[v] + 1;
 
            up[0][cur] = v;
            for (int j = 0; j <= lg - 1; j++) up[j + 1][cur] = up[j][up[j][cur]];
 
            ans[0][cur] = info(x);
            for (int j = 0; j <= lg - 1; j++) ans[j + 1][cur] = merge(ans[j][cur], ans[j][up[j][cur]]);
        } else {
            int u, v, x;
            cin >> u >> v >> x;
            u--; v--;
            
            if (d[u] < d[v]) swap(u, v);
 
            int dif = d[u] - d[v];
            info a, b;
            for (int i = lg; i >= 0; i--) {
                if ((dif >> i) & 1) {
                    a = merge(a, ans[i][u]);
                    u = up[i][u];
                }
            }
            if (u == v) {
                a = merge(a, ans[0][u]);
            } else {
                for (int i = lg; i >= 0; i--) {
                    if (up[i][u] != up[i][v]) {
                        a = merge(a, ans[i][u]);
                        u = up[i][u];
                        b = merge(b, ans[i][v]);
                        v = up[i][v];
                    }
                }
 
                a = merge(a, ans[1][u]);
                b = merge(b, ans[0][v]);
            }
 
            swap(b.minPrefL, b.minPrefR);
            swap(b.maxPrefL, b.maxPrefR);
 
            info res = merge(a, b);
            if (res.minSeg <= x && x <= res.maxSeg) {
                cout << "Yes\n";
            } else {
                cout << "No\n";
            }
        }
    }
}
 
int main() {
    int tests;
    cin >> tests;
    while (tests--) {
        solve();
    }
} 

//  w