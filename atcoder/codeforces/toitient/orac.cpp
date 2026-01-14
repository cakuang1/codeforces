#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll gcdll(ll a, ll b) { return b ? gcdll(b, a % b) : a; }
ll lcmll(ll a, ll b) { return a / gcdll(a, b) * b; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<ll> a(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];

    vector<ll> pre(n + 2, 0), suf(n + 2, 0);
    for (int i = 1; i <= n; ++i)
        pre[i] = gcdll(pre[i - 1], a[i]);
    for (int i = n; i >= 1; --i)
        suf[i] = gcdll(suf[i + 1], a[i]);

    ll ans = 1;
    for (int i = 1; i <= n; ++i) {
        ll di = gcdll(pre[i - 1], suf[i + 1]);
        ans = lcmll(ans, di);
    }

    cout << ans << "\n";
    return 0;
}


// wecoutw nwthe uw nbusmr wr paris that ar ecopriwmr w? ww

// ifx whtis snubmer ww