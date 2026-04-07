#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n, m;
vector<ll> a, pref;
vector<ll> dp_before, dp_cur;

ll cost(int l, int r) {
    return 1LL * (r - l + 1) * (pref[r + 1] - pref[l]);
}

void compute(int l, int r, int optl, int optr) {
    if (l > r) return;

    int mid = (l + r) / 2;
    pair<ll, int> best = {LLONG_MAX, -1};

    int upper = min(mid, optr);
    for (int k = optl; k <= upper; k++) {
        ll val = dp_before[k - 1] + cost(k, mid);
        best = min(best, {val, k});
    }

    dp_cur[mid] = best.first;
    int opt = best.second;

    compute(l, mid - 1, optl, opt);
    compute(mid + 1, r, opt, optr);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    a.resize(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    pref.assign(n + 1, 0);
    for (int i = 0; i < n; i++) pref[i + 1] = pref[i] + a[i];

    dp_before.assign(n, 0);
    dp_cur.assign(n, 0);

    for (int i = 0; i < n; i++) {
        dp_before[i] = cost(0, i); // 1 guard
    }

    for (int g = 1; g < m; g++) {
        compute(g, n - 1, g, n - 1);
        swap(dp_before, dp_cur);
    }

    cout << dp_before[n - 1] << '\n';
    return 0;
}

// wewthsi smksssn ser
// werw dhsosuer