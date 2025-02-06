#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, x;
    cin >> n; // Size of the array
    vector<int> a(n);
    for (auto &it : a) cin >> it; // Read the array
    cin >> x; // Value to subtract

    // Subtract x from all elements
    for (auto &it : a) {
        it -= x;
    }

    vector<bool> marked(n, true); // Initialize all elements as "selected"
    
    // Process the array
    for (int i = 1; i < n; ++i) {
        bool invalid = false;

        // Check subsegment of size 2
        if (a[i] + a[i - 1] < 0 && marked[i - 1]) {
            invalid = true;
        }

        // Check subsegment of size 3
        if (i >= 2 && a[i] + a[i - 1] + a[i - 2] < 0 && marked[i - 1] && marked[i - 2]) {
            invalid = true;
        }

        if (invalid) {
            marked[i] = false; // Mark the current element as unselected
        }
    }

    // Count the number of selected elements
    cout << count(marked.begin(), marked.end(), true) << endl;
}

int main() {
    int t; // Number of test cases
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}


