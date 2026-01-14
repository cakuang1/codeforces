#include <bits/stdc++.h>
using namespace std;
 
// We'll use __gcd from <numeric> or <algorithm>
 
int n;
vector<int> a; // We'll store the n vertex values in 1-indexed order

// dp[l][r][side]:
//   side == 0 means: can we build a valid subtree from indices l to r 
//                that attaches as the right child of a parent at index l-1?
//   side == 1 means: can we build a valid subtree from indices l to r 
//                that attaches as the left child of a parent at index r+1?
// If the subtree [l..r] is empty (l > r) we return true.
 
// We use -1 for uncomputed, 0 for false, and 1 for true.
int dp[705][705][2];
 
// Recursive function with memoization
int solve_dp(int l, int r, int side) {
    // Base: empty segment is always valid.
    if(l > r) return 1;
    // For dp(l, r, 0), the parent is at index (l-1) so l must be > 1.
    // Similarly for dp(l, r, 1), the parent is at index (r+1) so r must be < n.
    if(side == 0 && l == 1) return 0;
    if(side == 1 && r == n) return 0;
    
    if(dp[l][r][side] != -1)
        return dp[l][r][side];
    
    int res = 0;
    // Determine parent's value:
    int parent_val;
    if(side == 0) {
        // For state 0, the parent is at index l-1.
        parent_val = a[l-1];
    } else {
        // For state 1, the parent is at index r+1.
        parent_val = a[r+1];
    }
    
    // Try every candidate i in [l, r] as the root for this segment.
    for (int i = l; i <= r; i++) {
        // Check the gcd condition between parent's value and candidate's value.
        if(__gcd(parent_val, a[i]) == 1)
            continue;
        // For the left subtree [l, i-1]:
        // It must attach as the right child of candidate i.
        int left_ok = 1;
        if(l <= i-1)
            left_ok = solve_dp(l, i-1, 1);
        // For the right subtree [i+1, r]:
        // It must attach as the left child of candidate i.
        int right_ok = 1;
        if(i+1 <= r)
            right_ok = solve_dp(i+1, r, 0);
        if(left_ok && right_ok) {
            res = 1;
            break;
        }
    }
    dp[l][r][side] = res;
    return res;
}
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    cin >> n;
    a.resize(n+1);  // using 1-indexing
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    
    // We will try every vertex as the overall root.
    // For an overall tree, there is no parent's constraint.
    // So for candidate i, we need:
    //    - the left subtree [1, i-1] to be valid when attached to candidate i,
    //      which corresponds to dp(1, i-1, 1) if i > 1,
    //    - the right subtree [i+1, n] to be valid when attached to candidate i,
    //      which corresponds to dp(i+1, n, 0) if i < n.
    memset(dp, -1, sizeof(dp));
    bool possible = false;
    for (int i = 1; i <= n; i++){
        bool left_ok = true, right_ok = true;
        if(i > 1)
            left_ok = solve_dp(1, i-1, 1);
        if(i < n)
            right_ok = solve_dp(i+1, n, 0);
        if(left_ok && right_ok) {
            possible = true;
            break;
        }
    }
    
    cout << (possible ? "Yes" : "No") << "\n";
    return 0;
}
