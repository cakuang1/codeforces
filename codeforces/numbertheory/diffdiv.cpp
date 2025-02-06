#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Function to calculate GCD
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);

        // Read the array
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }

        // Separate even and odd numbers
        vector<int> evens, odds;
        for (int i = 0; i < n; ++i) {
            if (a[i] % 2 == 0) {
                evens.push_back(a[i]);
            } else {
                odds.push_back(a[i]);
            }
        }

        // Reorder the array: evens first, then odds
        a.clear();
        a.insert(a.end(), evens.begin(), evens.end());
        a.insert(a.end(), odds.begin(), odds.end());

        // Count good pairs
        int count = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (gcd(a[i], 2 * a[j]) > 1) {
                    count++;
                }
            }
        }

        // Output the result for the current test case
        cout << count << endl;
    }

    return 0;
}
