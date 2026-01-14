#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, l;
    cin >> n >> l;

    vector<ll> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    // Add endpoints 0 and l
    sort(nums.begin(), nums.end());

    // Calculate the maximum gap between adjacent lanterns
    ld maxGap = 0;
    for (int i = 1; i < n; i++) {
        maxGap = max(maxGap, (ld)(nums[i] - nums[i - 1]));
    }

    // Find the maximum distance at the ends of the street
    ld maxEndGap = max((ld)nums[0], (ld)(l - nums[n - 1]));

    // The required radius d
    ld res = max(maxEndGap, maxGap / 2.0);

    cout << fixed << setprecision(9) << res << endl;

    return 0;
}
