#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        ll n, k;
        cin >> n >> k;

        // Compute total = sum_{i=1..n} (k + (i-1)) = n*k + n*(n-1)/2
        ll total = n * k + (n * (n - 1) / 2);

        // A helper to compute S(i) = i*k + i*(i-1)/2
        auto S = [&](ll i) {
            return i * k + (i * (i - 1) / 2);
        };

        // Binary‐search for the smallest i in [1..n] with 2*S(i) >= total
        ll left = 1, right = n;
        while (left < right) {
            ll mid = left + (right - left) / 2;
            ll val = 2 * S(mid);
            if (val >= total) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        ll i0 = left;  

        // Compute candidate cost at i0
        ll best = llabs(2 * S(i0) - total);

        // If i0 > 1, also try i0 - 1
        if (i0 > 1) {
            ll c2 = llabs(2 * S(i0 - 1) - total);
            best = min(best, c2);
        }
        
        cout << best << "\n";
    }

    return 0;
}
