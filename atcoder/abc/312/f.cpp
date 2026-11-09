
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<ll> a, b, c;

    for (int i = 0; i < n; i++) {
        int t;
        ll x;
        cin >> t >> x;

        if (t == 0) a.push_back(x);
        if (t == 1) b.push_back(x);
        if (t == 2) c.push_back(x);
    }

    sort(a.rbegin(), a.rend());
    sort(b.rbegin(), b.rend());
    sort(c.rbegin(), c.rend());

    // Prefix sums of Type 0 and Type 1 happiness
    vector<ll> pa(a.size() + 1, 0);
    vector<ll> pb(b.size() + 1, 0);

    for (int i = 0; i < (int)a.size(); i++)
        pa[i + 1] = pa[i] + a[i];

    for (int i = 0; i < (int)b.size(); i++)
        pb[i + 1] = pb[i] + b[i];

    ll ans = pa[min(m, (int)a.size())];

    ll capacity = 0;
    int openers = 0;

    for (int k = 1; k <= min(m, (int)b.size()); k++) {

        // Obtain enough opener capacity for k regular cans
        while (capacity < k && openers < (int)c.size()) {
            capacity += c[openers];
            openers++;
        }

        if (capacity < k) break;

        // k regular cans + openers must fit in M slots
        if (k + openers > m) break;

        int remaining = m - k - openers;

        // Fill remaining slots with the best Type 0 cans
        int take = min(remaining, (int)a.size());

        ll total = pb[k] + pa[take];

        ans = max(ans, total);
    }

    cout << ans << '\n';

    return 0;
}
