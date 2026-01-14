#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int B = 24;  // only first 24 letters a..x

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    vector<ll> f(1 << B, 0);

    // Step 1: Process each word
    for (int i = 0; i < n; i++) {
        string s; cin >> s;

        // get unique letters in this word
        vector<int> letters;
        for (char c : s) letters.push_back(c - 'a');
        sort(letters.begin(), letters.end());
        letters.erase(unique(letters.begin(), letters.end()), letters.end());

        int sz = letters.size();

        // Step 2: Inclusion-exclusion
        // For every non-empty subset of the word's letters
        for (int st = 1; st < (1 << sz); st++) {
            int mask = 0, cnt = 0;
            for (int j = 0; j < sz; j++) {
                if (st & (1 << j)) {
                    mask |= (1 << letters[j]);
                    cnt++;
                }
            }
            if (cnt % 2 == 1) f[mask] += 1;   // odd sized subset → +1
            else              f[mask] -= 1;   // even sized subset → -1
        }
    }

    // Step 3: SOS DP (subset DP)
    for (int b = 0; b < B; b++) {
        for (int mask = 0; mask < (1 << B); mask++) {
            if (mask & (1 << b)) {
                f[mask] += f[mask ^ (1 << b)];
            }
        }
    }

    // Step 4: XOR of squared answers
    ll ans = 0;
    for (int mask = 0; mask < (1 << B); mask++) {
        ll val = f[mask];
        ans ^= (val * val);
    }

    cout << ans << "\n";
    return 0;
}
