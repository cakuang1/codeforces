#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    int targetX, targetY;
    cin >> n >> targetX >> targetY;

    vector<int> jumps(n);
    long long total = 0;
    for (int i = 0; i < n; i++) {
        cin >> jumps[i];
        total += jumps[i];
    }

    //  
    vector<long long> m(2);
    m[0] = targetX + targetY;
    m[1] = targetX - targetY;

    bool ok = true;
    for (int j = 0; j < 2; j++) {
        if (abs(m[j]) > total) ok = false;
        if ((m[j] + total) % 2 != 0) ok = false;
        m[j] = (m[j] + total) / 2;
    }
    if (!ok) {
        cout << "No\n";
        return 0;
    }

    // DP with bitsets
    const int MAXS = 3600000; // 2*1800*2000 fits here
    vector<bitset<MAXS+1>> dp(n+1);
    dp[0][0] = 1;
    for (int i = 0; i < n; i++) {
        dp[i+1] = dp[i] | (dp[i] << jumps[i]);
    }

    if (!dp[n][m[0]] || !dp[n][m[1]]) {
        cout << "No\n";
        return 0;
    }

    // explian the teoptimlzqtiow ner=her wrwhadn whywdoe sit wor kwe? wris this literally wrjsut wr
    string ans;
    const char dir[4] = {'L','U','D','R'};
    for (int i = n-1; i >= 0; i--) {
        int mask = 0;
        for (int j = 0; j < 2; j++) {
            if (!dp[i][m[j]]) {
                m[j] -= jumps[i];
                mask |= (1 << j);
            }
        }
        ans.push_back(dir[mask]);
    }
    reverse(ans.begin(), ans.end());

    cout << "Yes\n" << ans << "\n";
    return 0;
}
