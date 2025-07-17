#include<bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i] >> b[i];
    }
    vector<int> ord(n);
    for (int i = 0; i < n; ++i)
        ord[i] = i;
    sort(ord.begin(), ord.end(), [&](int i, int j) { return b[i] * (a[j] - 1) > b[j] * (a[i] - 1); });
    vector<long long> dp(k + 1, -1e9);
    dp[0] = 1;
    for (auto i : ord) {
        vector<long long> ndp = dp;
        for (int j = 0; j < k; ++j) if(dp[j] != -1e9) {
            ndp[j + 1] = max(ndp[j + 1], dp[j] * a[i] + b[i]);
        }
        dp = move(ndp);
    }
    cout << dp[k] << "\n";
}