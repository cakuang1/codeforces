#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, x;
    cin >> n >> x;
    vector<int> h(n), s(n), k(n);
    for(int i = 0; i < n; i++) cin >> h[i];
    for(int i = 0; i < n; i++) cin >> s[i];
    for(int i = 0; i < n; i++) cin >> k[i];

    vector<long long> dp(x+1, 0);

    // For each book, binary‐split its k[i] copies
    for(int i = 0; i < n; i++){
        int price = h[i];
        int pages = s[i];
        int cnt   = k[i];
        // split cnt into 1 + 2 + 4 + ... + remainder
        for(int b = 1; cnt > 0; b <<= 1){
            int take = min(b, cnt);
            cnt -= take;
            int w = price * take;    // combined weight
            int v = pages * take;    // combined value
            // 0–1 knapsack step
            for(int j = x; j >= w; j--){
                dp[j] = max(dp[j], dp[j - w] + v);
            }
        }
    }

    // answer = max pages for any total price ≤ x
    long long ans = 0;
    for(int j = 0; j <= x; j++){
        ans = max(ans, dp[j]);
    }
    cout << ans << "\n";
    return 0;
}
