#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, z;
    cin >> n >> z; 
    
    vector<int> nums(n);
    for (int i = 0; i < n; i++) { 
        cin >> nums[i]; 
    }

    // Sort the array to use a two-pointer approach effectively
    sort(nums.begin(), nums.end());

    int p1 = 0; // First pointer to track the lower value
    int p2 = n / 2; // Second pointer starts from the middle to look for possible matches
    int count = 0;

    // Two-pointer approach to find the maximum number of valid pairs
    while (p1 < n / 2 && p2 < n) {
        if (nums[p2] - nums[p1] >= z) {
            // A valid pair is found
            count++;
            p1++;
            p2++;
        } else {
            // If the difference is less than z, move `p2` to find a larger value
            p2++;
        }
    }

    // rmq works how how to see thsi w w

    cout << count << endl;
    return 0;
}
