#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, W;
    cin >> n >> W;

    vector<int> dp(W+1, 0); // size W+1

    for (int item = 0; item < n; item++) {
        int weight, val;
        cin >> weight >> val;
        for (int cap = W; cap >= weight; cap--) {
            dp[cap] = max(dp[cap], dp[cap - weight] + val);
        }
    }

    cout << dp[W] << "\n";
    return 0;
}
