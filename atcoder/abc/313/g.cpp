
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using i128 = __int128_t;

const ll MOD = 998244353;

// Returns sum_{i=0}^{n-1} floor((a*i+b)/m)
// Requires n >= 0, m >= 1, a >= 0, b >= 0.
i128 floor_sum(ll n, ll m, ll a, ll b) {
    i128 ans = 0;

    while (true) {
        if (a >= m) {
            ans += (i128)n * (n - 1) / 2 * (a / m);
            a %= m;
        }

        if (b >= m) {
            ans += (i128)n * (b / m);
            b %= m;
        }

        ll y = a * n + b;
        if (y < m) break;

        n = y / m;
        b = y % m;
        swap(m, a);
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<ll> a(n);
    for (ll &x : a) cin >> x;

    sort(a.begin(), a.end());

    ll mn = a[0];
    ll mx = a[n - 1];

    // All piles have equal size.
    if (mn == mx) {
        cout << (mn + 1) % MOD << '\n';
        return 0;
    }

    // p = 0, 1, ..., mn gives mn+1 distinct arrays.
    ll ans = (mn + 1) % MOD;

    ll p = mn + 1;
    int k = 0;
    ll prefix = 0;

    while (p <= mx) {
        // Piles with a[i] < p have already been emptied.
        while (k < n && a[k] < p) {
            prefix += a[k];
            k++;
        }

        // Number of piles still contributing p stones.
        ll cnt = n - k;

        // F(x) = prefix + cnt*x on [p, R].
        ll R = mx;
        if (k < n) {
            R = min(R, a[k]);
        }

        ll len = R - p + 1;

        // Sum_{x=p}^{R} floor(F(x) / n)
        i128 contribution = floor_sum(
            len,
            n,
            cnt,
            prefix + cnt * p
        );

        // Each x also allows q = 0.
        ans = (ans + (ll)(contribution % MOD)) % MOD;
        ans = (ans + len % MOD) % MOD;

        p = R + 1;
    }

    cout << ans << '\n';
    return 0;
}
