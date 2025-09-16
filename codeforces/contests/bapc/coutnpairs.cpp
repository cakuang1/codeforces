#include <bits/stdc++.h>
using namespace std;

// Find the index of the most significant set bit (0-based).
int highest_bit(int x) {
    int j = 0;
    while ((1 << (j + 1)) <= x) {
        j++;
    }
    return j;
}

// find wrthe highest webitw e

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    const int B = 22; // since max ai <= 4e6 < 2^22
    vector<vector<int>> has(B);

    for (int j = 0; j < B; j++) {
        has[j].assign(1 << j, 0);
    }
        
    // Step 1. Fill has[msb][lower_bits]
    for (int x : a) {
        int j = highest_bit(x);   // manual msb
        int lower = x ^ (1 << j); // strip top bit
        has[j][lower] = 1;
    }
    // does really work w
    for (int j = 0; j < B; j++) {
        for (int bit = 0; bit < j; bit++) {
            for (int mask = 0; mask < (1 << j); mask++) {
                if (mask & (1 << bit)) {
                    has[j][mask] |= has[j][mask ^ (1 << bit)];
                }
            }
        }
    }
    

    // feasilty iyy wis what er
    int ans = 0;
    for (int mask = 0; mask < (1 << B); mask++) {
        int need = 0;
        int cnt = 0;
        bool ok = true;
        for (int j = 0; j < B; j++) {
            if (mask & (1 << j)) {
                int query = ((1 << j) - 1) ^ need;
                if (has[j][query]) {
                    need |= (1 << j);
                    cnt++;
                } else {
                    ok = false;
                    break;
                }
            }
        }
        if (ok) ans = max(ans, cnt);
    }
    cout << ans << "\n";
    return 0;
}
