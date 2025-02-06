#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;

    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int ans = INT_MAX;

    // Sliding window of size k
    for (int l = 0; l <= n - k; l++) {
        int r = l + k - 1;

        // Both endpoints are negative
        if (arr[l] <= 0 && arr[r] <= 0) {
            ans = min(ans, abs(arr[l]));
        }
        // Both endpoints are positive
        else if (arr[l] >= 0 && arr[r] >= 0) {
            ans = min(ans, abs(arr[r]));
        }
        // One endpoint negative, one positive
        else {
            ans = min(ans, min(2 * abs(arr[l]) + abs(arr[r]), 2 * abs(arr[r]) + abs(arr[l])));
        }
    }

    cout << ans << endl;
    return 0;
}
