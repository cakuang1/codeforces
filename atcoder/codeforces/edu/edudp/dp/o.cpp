#include <bits/stdc++.h>  // Standard library for competitive programming
using namespace std;

const int MAX_SIZE = 1200300;  // Maximum possible size of array

int n, k;  // `n` = array size, `k` = max number of 0s allowed to flip
vector<int> arr(MAX_SIZE);  // Using a vector instead of a static array for flexibility

// Function to read input values
bool readInput() {
    if (!(cin >> n >> k)) {
        return false;  // Return false if input fails
    }
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    return true;
}

// Function to find the longest subarray with at most `k` zeroes flipped to ones
void solve() {
    int leftIndex = 0, rightIndex = 0;
    int j = 0, zeroCount = 0;  // `j` is the right boundary of the window, `zeroCount` is the count of zeroes in the window

    for (int i = 0; i < n; i++) {
        // Ensure the sliding window's left boundary is correctly placed
        if (j < i) {
            j = i;
            zeroCount = 0;
        }

        // Expand the right boundary `j` while keeping the number of zeroes <= k
        while (j < n) {
            int newZeroCount = zeroCount + (arr[j] == 0);  // Increment zero count if arr[j] is 0
            if (newZeroCount > k) {
                break;  // Stop expanding if more than `k` zeroes are present
            }
            zeroCount += (arr[j] == 0);
            j++;
        }
        // elongated werw
        // Update the best subarray found so far
        if (j - i > rightIndex - leftIndex) {
            leftIndex = i;
            rightIndex = j;
        }

        // If the leftmost element is zero, reduce the zero count before moving the left boundary
        if (zeroCount > 0) {
            zeroCount -= (arr[i] == 0);
        }
    }

    // Output the length of the longest valid subarray
    cout << (rightIndex - leftIndex) << endl;

    // Modify the array by setting elements in the chosen subarray to 1
    for (int i = leftIndex; i < rightIndex; i++) {
        arr[i] = 1;
    }

    // Print the modified array
    for (int i = 0; i < n; i++) {
        if (i > 0) {
            cout << " ";
        }
        cout << arr[i];
    }
    cout << endl;
}

// Main function
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);  // Optimize I/O speed

    if (readInput()) {
        solve();
    }

    return 0;
}
