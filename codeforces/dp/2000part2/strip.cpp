#include <bits/stdc++.h>
using namespace std;
 
const int INF = 1e9;
 
// Segment tree for range minimum queries on dp array.
struct SegTree {
    int size;
    vector<int> tree;
    
    SegTree(int n) {
        size = 1;
        while(size < n) size *= 2;
        tree.assign(2 * size, INF);
    }
    
    // Update index idx (0-indexed) with value val.
    void update(int idx, int val) {
        idx += size;
        tree[idx] = val;
        for (idx /= 2; idx >= 1; idx /= 2) {
            tree[idx] = min(tree[2*idx], tree[2*idx+1]);
        }
    }
    
    // Query the minimum value in the range [l, r] (0-indexed).
    int query(int l, int r) {
        int res = INF;
        l += size;
        r += size;
        while(l <= r) {
            if(l % 2 == 1) res = min(res, tree[l++]);
            if(r % 2 == 0) res = min(res, tree[r--]);
            l /= 2; r /= 2;
        }
        return res;
    }
};
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, s, l;
    cin >> n >> s >> l;
    vector<int> a(n);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    
    // If a piece must contain at least l elements and n < l, it's impossible.
    if(l > n) {
        cout << -1 << "\n";
        return 0;
    }
    
    // --- Preprocessing: Compute left[i] for each i ---
    // left[i] = smallest index j such that [j, i] is valid.
    vector<int> leftIdx(n);
    deque<int> minD, maxD;
    int j = 0;
    for (int i = 0; i < n; i++){
        // Update min deque: Remove indices with values >= a[i]
        while(!minD.empty() && a[minD.back()] >= a[i])
            minD.pop_back();
        minD.push_back(i);
        
        // Update max deque: Remove indices with values <= a[i]
        while(!maxD.empty() && a[maxD.back()] <= a[i])
            maxD.pop_back();
        maxD.push_back(i);
        
        // Shrink window from left until valid: (max - min <= s)
        while(!minD.empty() && !maxD.empty() && (a[maxD.front()] - a[minD.front()] > s)) {
            if(minD.front() == j) minD.pop_front();
            if(maxD.front() == j) maxD.pop_front();
            j++;
        }
        leftIdx[i] = j;
    }
    
    // --- DP: dp[i] = minimum pieces to partition a[0..i-1] ---
    // dp[0] = 0 (no elements means 0 pieces)
    vector<int> dp(n+1, INF);
    dp[0] = 0;
    
    // Set up segment tree for dp range minimum queries.
    SegTree seg(n+1);
    seg.update(0, 0);
    
    // Compute dp[i] for i = l ... n.
    // We want the last segment to cover indices [j, i-1].
    // For [j, i-1] to be valid, we need j >= leftIdx[i-1] and also i - j >= l.
    // That is, j <= i - l.
    for (int i = l; i <= n; i++){
        int endSegment = i - l;  // last possible starting index for a segment ending at i-1
        // The segment [j, i-1] is valid if j >= leftIdx[i-1].
        int startSegment = leftIdx[i-1];
        if (startSegment > endSegment) continue;  // no valid segment ending at i-1
        int best = seg.query(startSegment, endSegment);
        if (best != INF) {
            dp[i] = best + 1;
            seg.update(i, dp[i]);
        }
    }
    
    // If dp[n] is still INF, there is no valid partition.
    cout << (dp[n] >= INF ? -1 : dp[n]) << "\n";
    
    return 0;
}
