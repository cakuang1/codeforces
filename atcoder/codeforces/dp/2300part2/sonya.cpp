#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;

struct Block {
    vector<ll> arr; // sorted list of d-values in this block
    ll median;     // median of arr
    ll cost;       // sum of |x - median| for x in arr
};

// Merge two blocks (each with sorted arr) into one sorted block.
// Recompute the median and cost.
Block mergeBlocks(const Block &b1, const Block &b2) {
    Block res;
    res.arr.resize(b1.arr.size() + b2.arr.size());
    merge(b1.arr.begin(), b1.arr.end(), b2.arr.begin(), b2.arr.end(), res.arr.begin());
    int size = res.arr.size();
    res.median = res.arr[size / 2];  // if even, any value between the two middles minimizes L1 error
    ll totalCost = 0;
    for (ll x : res.arr) {
        totalCost += abs(x - res.median);
    }
    res.cost = totalCost;
    return res;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    // We will process each element and maintain a stack of blocks
    // such that each block represents a contiguous segment where the optimal c is the median.
    vector<Block> st;
    for (int i = 0; i < n; i++) {
        // Compute d[i] = a[i] - (i+1) using 0-indexing.
        ll d = a[i] - (i + 1);
        Block curr;
        curr.arr.push_back(d);
        curr.median = d;
        curr.cost = 0;
        
        // If the previous block’s median is greater than current block's median,
        // then merging them will help satisfy the non-decreasing condition.
        while (!st.empty() && st.back().median > curr.median) {
            Block merged = mergeBlocks(st.back(), curr);
            st.pop_back();
            curr = merged;
        }
        st.push_back(curr);
    }
    
    // Sum up the cost from each block. This total cost is the answer.
    ll ans = 0;
    for (const Block &b : st) {
        ans += b.cost;
    }
    
    cout << ans << "\n";
    return 0;
}
        



// optimalw to mvoe back whacl e