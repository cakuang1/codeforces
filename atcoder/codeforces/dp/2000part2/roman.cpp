#include <bits/stdc++.h>
using namespace std;
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    cin >> s;
    int m;
    cin >> m;
    int n = s.size();
    
    // dp[mask][r] = number of ways to form a number using the digits in positions in 'mask'
    // so that its remainder modulo m is r.
    // There are at most 2^n masks and m remainders.
    vector<vector<long long>> dp(1 << n, vector<long long>(m, 0));
    dp[0][0] = 1;
    
    // Iterate over all masks (state representing which digits have been used)
    for (int mask = 0; mask < (1 << n); mask++){
        for (int r = 0; r < m; r++){
            if(dp[mask][r] == 0) continue;
            for (int j = 0; j < n; j++){
                // If j-th digit is not used in 'mask'
                if((mask & (1 << j)) == 0){
                    // If we're about to choose the first digit, do not allow a '0'
                    if(mask == 0 && s[j] == '0') continue;
                    int newMask = mask | (1 << j);
                    int newR = (r * 10 + (s[j] - '0')) % m;
                    dp[newMask][newR] += dp[mask][r];
                }
            }
        }
    }
    
    // Our answer is the number of full permutations (mask = (1<<n)-1) with remainder 0.
    long long res = dp[(1 << n) - 1][0];
    
    // Remove overcounting due to duplicate digits.
    // Count frequency of each digit.
    vector<int> counts(10, 0);
    for (char c : s) {
        counts[c - '0']++;
    }
    // Compute factorial (for numbers up to 18, 64-bit is safe)
    auto factorial = [&](int x) -> long long {
        long long ret = 1;
        for (int i = 2; i <= x; i++)
            ret *= i;
        return ret;
    };
    for (int d = 0; d < 10; d++){
        if(counts[d] > 1)
            res /= factorial(counts[d]);
    }
    
    cout << res << "\n";
    return 0;
}
