#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s, p;
    cin >> s >> p;
    int n = s.size(), m = p.size();
    
    // Precompute a[i]: minimal index j such that s[i..j] contains p as a subsequence.
    vector<int> a(n, INT_MAX);
    for (int i = 0; i < n; i++){
        int p_index = 0;
        for (int j = i; j < n; j++){
            if (s[j] == p[p_index]) {
                p_index++;
                if (p_index == m){
                    a[i] = j; // Found a complete subsequence for p
                    break;
                }
            }
        }
    }
    
    // dp[i][j]: maximum number of occurrences formed using s[0..i-1] with exactly j deletions.
    // Initialize with -1 (impossible states) and set dp[0][0] = 0 occurrences.
    vector<vector<int>> dp(n+1, vector<int>(n+1, -1));
    dp[0][0] = 0;
    
    // Process positions from 0 to n
    for (int i = 0; i < n; i++){
        for (int j = 0; j <= n; j++){
            if (dp[i][j] == -1)
                continue;
            // Option 1: Keep s[i] (do not delete) and do nothing special.
            dp[i+1][j] = max(dp[i+1][j], dp[i][j]);
            
            // Option 2: Delete s[i] (increment deletion count by 1).
            if(j + 1 <= n)
                dp[i+1][j+1] = max(dp[i+1][j+1], dp[i][j]);
            
            // Option 3: Use s[i..a[i]] to form an occurrence of p.
            if(a[i] != INT_MAX){
                int endIndex = a[i]; 
                int cost = (endIndex - i + 1) - m; // extra deletions needed in the segment
                if(j + cost <= n)
                    dp[endIndex + 1][j + cost] = max(dp[endIndex + 1][j + cost], dp[i][j] + 1);
            }
        }
    }
    vector<int> ans(n+1, 0);
    for (int j = 0; j <= n; j++){
        ans[j] = dp[n][j];
    }
    for (int j = 1; j <= n; j++){
        ans[j] = max(ans[j], ans[j-1]);
    }
    
    // Output answers for deletion counts from 0 to n.
    for (int j = 0; j <= n; j++){
        cout << ans[j] << " ";
    }
    cout << "\n";
    
    return 0;
}
