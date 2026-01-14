#include <bits/stdc++.h>
using namespace std;

static const int INF = 1000000007;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long s;
    int l;
    cin >> n >> s >> l;
    vector<long long> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    if(l > n){
        cout << -1 << "\n";
        return 0;
    }

    // 1) Compute can[i]: earliest j so that [j..i] has max-min ≤ s
    vector<int> can(n);
    deque<int> mindq, maxdq;
    int j = 0;
    for(int i = 0; i < n; i++){
        // push i into mindq (increasing) and maxdq (decreasing)
        while(!mindq.empty() && a[mindq.back()] > a[i]) 
            mindq.pop_back();
        mindq.push_back(i);
        while(!maxdq.empty() && a[maxdq.back()] < a[i]) 
            maxdq.pop_back();
        maxdq.push_back(i);

        // shrink window from left until max-min ≤ s
        while(j <= i && a[maxdq.front()] - a[mindq.front()] > s){
            if(mindq.front() == j) mindq.pop_front();
            if(maxdq.front() == j) maxdq.pop_front();
            j++;
        }
        can[i] = j;
    }

    // 2) DP with deque for range-min queries on dp[j]
    // dp[0] = 0, dp[i>0] = min #pieces for prefix of length i
    vector<int> dp(n+1, INF);
    dp[0] = 0;
    deque<int> dq;  // will store candidate j's in increasing dp[j] order
    for(int i = 1; i <= n; i++){
        // we can close a piece ending at i iff (i - l) >= can[i-1]
        int enter = i - l;
        if(enter >= 0){
            // push dp[enter] as a new candidate
            while(!dq.empty() && dp[dq.back()] >= dp[enter])
                dq.pop_back();
            dq.push_back(enter);
        }
        // pop any candidates j < can[i-1]
        int low = can[i-1];
        while(!dq.empty() && dq.front() < low)
            dq.pop_front();

        // dq.front() is the j giving min dp[j]
        if(!dq.empty()){
            dp[i] = dp[dq.front()] + 1;
        }
    }

    cout << (dp[n] >= INF ? -1 : dp[n]) << "\n";
    return 0;
}
