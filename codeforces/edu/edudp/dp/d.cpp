#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int MOD = 1000000007;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<ll> nums(n), t(n);
    vector<ll> prefix1(n + 1, 0), prefix2(n + 1, 0);

    for (int i = 0; i < n; i++) {
        cin >> nums[i];
        prefix1[i + 1] = prefix1[i] + nums[i];
    }

    for (int i = 0; i < n; i++) {
        cin >> t[i];
        prefix2[i + 1] = prefix2[i];
        if (t[i]) {
            prefix2[i + 1] += nums[i];
        }
    }

    ll ans = 0;
    // Sliding window over [l, r] with size = k
    for (int l = 0, r = k - 1; r < n; l++, r++) {
        // sum(t[i]) for i < l --> prefix2[l]
        // sum(all i) for l <= i <= r --> prefix1[r+1] - prefix1[l]
        // sum(t[i]) for i > r --> prefix2[n] - prefix2[r+1]
        ll candidate = prefix2[l]
            + (prefix1[r + 1] - prefix1[l])
            + (prefix2[n] - prefix2[r + 1]);
        ans = max(ans, candidate);
    }

    cout << ans << "\n";
    return 0;
}
