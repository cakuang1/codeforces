
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    ll k;
    cin >> n >> k;

    vector<pair<ll, ll>> a(n);

    ll mx = 0;

    for (auto &[days, pills] : a) {
        cin >> days >> pills;
        mx = max(mx, days);
    }

    ll l = 1, r = mx + 1;

    while (l < r) {
        ll mid = l + (r - l) / 2;

        ll sum = 0;

        for (auto [days, pills] : a) {
            if (days >= mid) {
                sum += pills;
            }
        }

        if (sum <= k) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }

    cout << l << '\n';
}
