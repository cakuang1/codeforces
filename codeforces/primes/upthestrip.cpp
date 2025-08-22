#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long m;
    cin >> n >> m;

    vector<int> dp(n+2, 0), pref(n+2, 0), add(n+3, 0);

    // Base case
    dp[1] = 1;
    pref[1] = 1;
    long long cur_add = 0;

    // Seed floored‐division contributions coming from x=1
    // For every z>=2, positions t with floor(t/z)=1 are t in [z, 2z-1]
    for (int z = 2, L = z; L <= n; z++, L = z) {
        int R = min(n, L + z - 1);
        add[L] = (add[L] + dp[1]) % m;
        if (R + 1 <= n)
            add[R+1] = (add[R+1] - dp[1] + m) % m;
    }

    // DP from x=2 to n
    for (int x = 2; x <= n; x++) {
        // incorporate range‐updates for floored‐division part
        cur_add = (cur_add + add[x]) % m;

        // dp[x] = sum_{y=1..x-1} dp[y]  +  sum_{z=2..x} dp[floor(x/z)]
        //
        dp[x] = ( (long long)pref[x-1] + cur_add ) % m;

        // update prefix-sum of dp
        pref[x] = (pref[x-1] + dp[x]) % m;

        // distribute dp[x] to all future t where floor(t/z)=x
        // for each z>=2 with x*z <= n:
        for (int z = 2, L = x*z; L <= n; z++, L = x*z) {
            int R = min(n, L + z - 1);
            add[L] = (add[L] + dp[x]) % m;
            if (R + 1 <= n)
                add[R+1] = (add[R+1] - dp[x] + m) % m;
        }
    }
    // doesthi wwork we weand erhow dou w wer
    cout << dp[n] << "\n";
    return 0;
}
