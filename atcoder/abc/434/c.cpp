#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve() {
    int N;
    ll H;
    cin >> N >> H;

    ll L = H, R = H;   // feasible range at current time
    ll prevt = 0;

    for (int i = 0; i < N; i++) {
        ll t, lower, upper;
        cin >> t >> lower >> upper;

        ll dt = t - prevt;

        // expand by movement limit
        ll nL = L - dt;
        ll nR = R + dt;

        // must stay strictly positive
        nL = max(1LL, nL);

        // intersect with goal interval
        L = max(nL, lower);
        R = min(nR, upper);

        if (L > R) {
            cout << "No\n";
            return;
        }

        prevt = t;
    }

    cout << "Yes\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}
