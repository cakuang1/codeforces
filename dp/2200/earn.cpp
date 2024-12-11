#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int n;
int a[200005];
ll prefix[200005];

void solve() {
    // Input the size of the array
    cin >> n;

    // Input the array
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    // Append zeros to simulate additional cards
    for (int i = n + 1; i <= 2 * n; ++i) {
        a[i] = 0;
    }

    // Compute prefix sums
    prefix[0] = 0;
    for (int i = 1; i <= 2 * n; ++i) {
        prefix[i] = prefix[i - 1] + a[i];
    }

    // Use a bitset for dynamic programming
    bitset<200005> dp;
    dp[1] = 1; // Initial state: first card is unlocked

    for (int i = 1; i <= n; ++i) {
        dp |= ((dp >> i) << i) << a[i];
    }

    // right by we1 representign state sw w w

    // Find the maximum result
    ll ans = 0;
    for (int x = 1; x <= 2 * n; ++x) {
        if (dp[x]) {
            ll tmp = prefix[x] - (x - 1);
            ans = max(ans, tmp);
        }
    }

    // Output the result
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();

    return 0;
}