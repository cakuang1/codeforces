
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<long long> a(n), pref(n, 0);

    for (auto &x : a) cin >> x;

    for (int i = 1; i < n; i++) {
        pref[i] = pref[i - 1];

        if (i % 2 == 0) {
            pref[i] += a[i] - a[i - 1];
        }
    }

    auto get = [&](long long t) -> long long {
        int i = upper_bound(a.begin(), a.end(), t)
                - a.begin() - 1;

        long long res = pref[i];

        if (i % 2 == 1) {
            res += t - a[i];
        }

        return res;
    };

    int q;
    cin >> q;

    while (q--) {
        long long l, r;
        cin >> l >> r;

        cout << get(r) - get(l) << '\n';
    }
}
