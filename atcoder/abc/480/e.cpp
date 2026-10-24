#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using i128 = __int128_t;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    cin >> N;

    // Checks a * (a+d) * ... * (a+(len-1)*d) <= N.
    auto valid = [&](ll a, ll d, int len) -> bool {
        i128 product = 1;

        for (int i = 0; i < len; i++) {
            product *= a + i * d;
            if (product > N) return false;
        }

        return true;
    };

    ll ans = 0;

    for (int len = 3; len <= 19; len++) {
        // The smallest sequence of this length is (1, 2, ..., len).
        if (!valid(1, 1, len)) break;

        // Maximum valid d cannot increase as a increases.
        ll upper = 1'000'000'000;

        for (ll a = 1; valid(a, 1, len); a++) {
            ll lo = 1;     // Valid difference.
            ll hi = upper; // Invalid difference.

            while (hi - lo > 1) {
                ll mid = lo + (hi - lo) / 2;

                if (valid(a, mid, len))
                    lo = mid;
                else
                    hi = mid;
            }

            // All differences 1, 2, ..., lo are valid.
            ans += lo;
            upper = lo + 1;
        }
    }

    cout << ans << '\n';
}

