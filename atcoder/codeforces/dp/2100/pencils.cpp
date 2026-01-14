#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, k;
    long long d;
    cin >> n >> k >> d;
    vector<long long> a(n);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    
    // dp[i] = true if we can partition the first i pencils into valid boxes.
    vector<bool> dp(n + 1, false);
    dp[0] = true;
    
    // prefix sum to quickly check if any dp[j] in a range is true.
    vector<int> prefix(n + 1, 0);
    prefix[0] = 1;
    
    int lp = 0;
    for (int i = 1; i <= n; i++){
        // We are considering the block ending at pencil index i-1.
        // Move lp so that the pencils from lp to i-1 have difference at most d.
        while (lp < i && a[i - 1] - a[lp] > d) {
            lp++;
        }
        
        // We need at least k pencils in the current box.
        if (i - lp >= k) {
            // We want to see if there exists a j in [lp, i - k] (as partition index)
            // such that dp[j] is true. We can use the prefix sum array for that.
            int leftRange = lp;
            int rightRange = i - k;
            int sum = prefix[rightRange] - (leftRange > 0 ? prefix[leftRange - 1] : 0);
            if (sum > 0) {
                dp[i] = true;
            }
        }
        
        // Update the prefix sum.
        prefix[i] = prefix[i - 1] + (dp[i] ? 1 : 0);
    }
    
    cout << (dp[n] ? "YES" : "NO") << "\n";
    return 0;
}
