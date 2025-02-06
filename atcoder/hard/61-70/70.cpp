#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<int> a(n), b(n), c(n);

    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];
    for (int i = 0; i < n; i++) cin >> c[i];

    // Step 1: Sort the three arrays
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    sort(c.begin(), c.end());

    // Step 2: Compute `bend[i]`: The number of `a` values that are < `b[i]`
    vector<ll> bend(n, 0);
    int p = 0;
    for (int i = 0; i < n; i++) {
        while (p < n && a[p] < b[i]) {
            p++;
        }
        bend[i] = p; // Store the count of valid `a` elements for `b[i]`
    }

    // Step 3: Compute the cumulative sum of `bend[i]`
    vector<ll> prefixSum(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        prefixSum[i] = prefixSum[i - 1] + bend[i - 1];
    }

    // Step 4: Compute the total number of valid altars
    ll res = 0;
    int p2 = 0;
    for (int i = 0; i < n; i++) {
        while (p2 < n && b[p2] < c[i]) {
            p2++;
        }
        res += prefixSum[p2]; // Use prefix sum to count valid `(a, b)` pairs
    }

    cout << res << endl;
    return 0;
}
