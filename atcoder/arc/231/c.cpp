
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve() {
    int n;
    cin >> n;

    vector<ll> a(n), b(n);

    for (auto &x : a) cin >> x;
    for (auto &x : b) cin >> x;

    // Returns true if both endpoints of person i
    // are forbidden by their immediate neighbors.
    auto bad = [&](int i) -> bool {
        if (i < 0 || i >= n) return false;

        ll l = a[i] - b[i];
        ll r = a[i] + b[i];

        bool leftBlocked = false;
        bool rightBlocked = false;

        for (int j : {i - 1, i + 1}) {
            if (j < 0 || j >= n) continue;

            ll L = a[j] - b[j];
            ll R = a[j] + b[j];

            if (L < l && l < R)
                leftBlocked = true;

            if (L < r && r < R)
                rightBlocked = true;
        }

        return leftBlocked && rightBlocked;
    };

    int badCount = 0;

    for (int i = 0; i < n; i++) {
        badCount += bad(i);
    }

    int q;
    cin >> q;

    while (q--) {
        int p;
        ll s;
        cin >> p >> s;
        --p;

        // Remove old contributions
        for (int i = p - 1; i <= p + 1; i++) {
            badCount -= bad(i);
        }

        // Apply update
        b[p] = s;

        // Add new contributions
        for (int i = p - 1; i <= p + 1; i++) {
            badCount += bad(i);
        }

        cout << (badCount == 0 ? "Yes" : "No") << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}
