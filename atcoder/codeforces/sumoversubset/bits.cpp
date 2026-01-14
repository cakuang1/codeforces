#include <bits/stdc++.h>
using namespace std;

void add(vector<pair<int,int>>& dp , int index, int mask) {
    if (index == -1) return;
    if (dp[mask].second < index) {
        dp[mask].first = dp[mask].second;
        dp[mask].second = index;
    } else if (dp[mask].first < index) {
        dp[mask].first = index; 
    }
}

int main()  {
    ios_base::sync_with_stdio(0); cin.tie(0);  
    int n; cin >> n;
    vector<int> arr(n);
    for (int i = 0 ; i < n; i ++) cin >> arr[i];

    int B = log2(2000000) + 1; // 21 bits
    vector<pair<int,int>> dp(1 << B, {-1,-1}); 

    // base fill
    for (int i = 0 ; i < n; i ++) {
        add(dp, i, arr[i]); 
    }
    

    for (int i = 0 ; i < B ; i++) { 
        for (int mask = 0 ; mask < (1 << B) ; mask++) {
            if (!(mask & (1 << i))) {
                if (dp[mask | (1 << i)].first != -1) 
                    add(dp, dp[mask | (1 << i)].first, mask);
                if (dp[mask | (1 << i)].second != -1) 
                    add(dp, dp[mask | (1 << i)].second, mask);
            }
        }
    } 

    int res = 0; 
    for (int i = 0 ; i < n - 2 ; i++) {
        int opt = 0; 
        int val = arr[i]; 

        for (int bit = B-1 ; bit >= 0 ; bit--) {
            if (val & (1 << bit)) continue;
            auto p = dp[opt | (1 << bit)]; 
            if (p.first > i && p.second > i) {
                opt |= (1 << bit);
            }
        }    
        res = max(res, val | opt); 
    }

    cout << res << "\n"; 
    return 0;
}


