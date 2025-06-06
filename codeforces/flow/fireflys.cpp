#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;
        vector<ll> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        // Build prefix sums of a: pref[i] = sum of a[0..i-1], pref[0]=0
        vector<ll> pref(n+1, 0);
        for (int i = 0; i < n; i++) {
            pref[i+1] = pref[i] + a[i];
        }
        ll S = pref[n];  // total sum of one full array a

        auto sumUpTo = [&](ll P) -> ll {
            // Returns sum of B[0..P], where B is the concatenation
            // of all n cyclic shifts of a.
            if (P < 0) return 0LL;
            // Number of elements considered = P+1
            ll count = P + 1;
            ll fullBlocks = count / n;    // how many complete cyclic-shift blocks
            int rem = int(count % n);     // how many extra elements in the next block
            ll ans = fullBlocks * S;

            if (rem > 0) {
                // The next block is the (fullBlocks)-th zero-based block, i.e. shift index = fullBlocks % n
                int st = int(fullBlocks % n);
                // We need sum of a[st..st+rem-1] modulo wrap at n
                if (st + rem <= n) {
                    ans += pref[st + rem] - pref[st];
                } else {
                    // Wrap around
                    ll part1 = pref[n] - pref[st];
                    ll part2 = pref[(st + rem) - n] - pref[0];
                    ans += (part1 + part2);
                }
            }
            return ans;
        };

        while (q--) {
            ll l, r;
            cin >> l >> r;
            // Convert to 0-based
            ll L = l - 1;
            ll R = r - 1;
            ll answer = sumUpTo(R) - sumUpTo(L - 1);
            cout << answer << "\n";
        }
    }

    return 0;
}

//