#include <bits/stdc++.h>
using namespace std;

vector<int> a;
vector<int> b;
int n, k;

// Function to check if we can bake `thresh` cookies
bool check(int thresh) {
    long long rem = k; // Remaining magic powder
    for (int i = 0; i < n; i++) {
        long long required = 1LL * a[i] * thresh; // Grams needed for `thresh` cookies
        if (required > b[i]) {
            rem -= (required - b[i]); // Use magic powder for the shortage
            if (rem < 0) return false; // Not enough magic powder
        }
    }
    return true; // All shortages covered
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k;
    a.resize(n);
    b.resize(n);

    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];

    int left = 0, right = 2e9; // Set a sufficiently large upper bound
    int res = 0;

    // Binary search for the maximum number of cookies
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (check(mid)) {
            res = mid; // Try for a higher number
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    cout << res << "\n";
    return 0;
}


// ano