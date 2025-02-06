#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

using ll = long long;
const ll MOD = 1e9 + 7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    // Count inversions within one array (intra-array inversions)
    ll intra_inversions = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[i] > a[j]) {
                intra_inversions++;
            }
        }
    }
    intra_inversions %= MOD;

    // Count inversions between different copies of A (inter-array inversions)
    ll inter_inversions = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i] > a[j]) {
                inter_inversions++;
            }
        }
    }
    inter_inversions %= MOD;

    // Total inversions
    ll ans = 0;
    ans += (intra_inversions * k) % MOD; // Intra-array inversions in all copies
    ans %= MOD;

    // Inter-array inversions
    ll pairs = (1LL * k * (k - 1) / 2) % MOD; // Sum of first k-1 numbers
    ans += (inter_inversions * pairs) % MOD;
    ans %= MOD;

    cout << ans << endl;
    return 0;
}
