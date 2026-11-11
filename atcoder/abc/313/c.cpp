
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<ll> a(n);
    ll sum = 0;

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sum += a[i];
    }

    sort(a.begin(), a.end());

    ll q = sum / n;
    ll r = sum % n;

    ll ans = 0;

    for (int i = 0; i < n; i++) {
        ll target = q;

        // Largest r elements should become q + 1
        if (i >= n - r) {
            target++;
        }

        ans += abs(a[i] - target);
    }

    // Each operation fixes 2 units of absolute difference
    cout << ans / 2 << '\n';

    return 0;
}
