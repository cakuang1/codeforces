#include <bits/stdc++.h>
using namespace std;
using ld = long double;
using ll = long long;

const int MAX_N = 51;
ld dp[MAX_N][MAX_N][MAX_N * MAX_N]; // dp[i][j][s] -> Ways to seat j guests from first i guests with sum s
ll fact[MAX_N]; // Factorials

void precomputeFactorials() {
    fact[0] = 1;
    for (int i = 1; i < MAX_N; i++) {
        fact[i] = fact[i - 1] * i;
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int n, p;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    cin >> p;
    
    precomputeFactorials();
    
    ld expectedValue = 0;
    
    for (int h = 0; h < n; h++) { // Fix the last guest that cannot be seated
        memset(dp, 0, sizeof(dp));
        dp[0][0][0] = 1; // Base case: 0 guests with sum 0
        
        for (int i = 0; i < n; i++) {
            if (i == h) continue; // Skip the fixed guest
            for (int j = n - 1; j >= 0; j--) {
                for (int s = p - a[h]; s >= 0; s--) {
                    if (dp[i][j][s] > 0) {
                        dp[i + 1][j + 1][s + a[i]] += dp[i][j][s];
                    }
                }
            }
        }
        
        for (int i = 0; i < n; i++) {
            for (int s = 0; s <= p - a[h]; s++) {
                expectedValue += dp[n][i][s] * fact[i] * fact[n - 1 - i];
            }
        }
    }

    // probability to play the map we
    expectedValue /= fact[n];
    cout << fixed << setprecision(9) << expectedValue << "\n";
    return 0;
}
