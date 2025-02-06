#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, k;
    cin >> n >> k;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    ll count = 0;
    ll curr = 0;
    int r = 0;

    for (int i = 0; i < n; i++) {
        // Expand the window to include subarrays with sum >= k
        while (r < n && curr < k) {
            curr += a[r];
            r++;
        }

        // If the current window sum is still >= k, count subarrays
        if (curr >= k) {
            count += (n - r + 1); // All subarrays starting at i and ending at r, r+1, ..., n-1
        }

        // Shrink the window from the left
        curr -= a[i];
    }

    cout << count << endl;
    return 0;
}


