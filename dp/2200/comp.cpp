#include <bits/stdc++.h>
using namespace std;

const int K = 22;               // Maximum bit length
const int MAX_MASK = (1 << K);  // 2^22
vector<int> z(MAX_MASK, 0);     // DP table to track reachable masks
vector<int> parent(MAX_MASK, -1); // To store contributors for z[mask]

// Precompute the DP table
void precomputeDP(const vector<int>& a) {
    for (int num : a) {
        z[num] = 1;          // Each number can reach itself
        parent[num] = num;   // Store the number that contributes
    }

    // Update states based on transitions
    for (int mask = 0; mask < MAX_MASK; mask++) {
        if (z[mask]) { // If the current mask is reachable
            for (int j = 0; j < K; j++) {
                if (!(mask & (1 << j))) { // If the j-th bit is `0`
                    int new_mask = mask | (1 << j);
                    if (!z[new_mask]) {
                        z[new_mask] = 1;
                        parent[new_mask] = parent[mask]; // Propagate contributor
                    }
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // Precompute the DP table
    precomputeDP(a);
    // Answer queries
    for (int i = 0; i < n; i++) {
        // Compute y = ~x & ((1 << K) - 1)
        int x = a[i];
        int y = (~x) & ((1 << K) - 1);
 
        if (z[y]) {
            cout << parent[y] << " ";
        } else {
            cout << -1 << " ";
        }
    }
    cout << endl;

    return 0;
}
