#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int depth(ll n) {
    int d = 0;
    while (true) {
        n >>= 1;
        if (!n) break;
        ++d;
    }
    return d;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        ll n, x, k;
        cin >> n >> x >> k;
        int dn = depth(n);
        int dx = depth(x);
        ll ans = 0;
        for (int i = 0; i <= dx; i++) { // i = depth(lca(x, y))
            if (dx - i > k) continue;
            if (i + k - (dx - i) > dn) continue;
            ll l, r;
            if (i == dx) {
                l = x << k;
                r = (x + 1) << k;
            } else {
                ll z = x >> (dx - i);
                if (dx - i < k) {
                    l = z * 2 + (~x >> (dx - i - 1) & 1);
                    l <<= (k - (dx - i) - 1);
                    r = l + (1LL << (k - (dx - i) - 1));
                } else {
                    l = z, r = z + 1;
                }
            }
            if (l > n) continue;
            r = min(r, n + 1);
            ans += r - l;
        }
        cout << ans << '\n';
    }
}
 