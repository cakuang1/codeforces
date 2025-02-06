#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    ll n; 
    cin >> n; 
    vector<ll> worms(n); 
    vector<ll> prefix(n); 
    
    for (int i = 0; i < n; i++) {
        cin >> worms[i];
    }

    // Compute prefix sums
    prefix[0] = worms[0];
    for (int i = 1; i < n; i++) {
        prefix[i] = prefix[i - 1] + worms[i]; 
    }
    
    ll queries;
    cin >> queries;

    for (int i = 0; i < queries; i++) {
        ll query;
        cin >> query; 

        // Binary search to find the pile containing the worm
        int res = -1;
        int left = 0, right = n - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (query <= prefix[mid]) {
                res = mid;
                right = mid - 1; // Move left to find the first occurrence
            } else {
                left = mid + 1;
            }
        }

        // Output the 1-based index of the pile
        cout << res + 1 << endl;
    }

    return 0;
}
