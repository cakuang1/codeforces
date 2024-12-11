#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Segment tree data structure
struct SegmentTree {
    vector<ll> tree;
    int size;
    
    // Initialize segment tree with a given size
    SegmentTree(int n) {
        size = n;
        tree.assign(4 * n, 0);
    }

    // Update a specific position
    void update(int idx, int left, int right, int pos, ll value) {
        if (left == right) {
            tree[idx] += value; // Add value at position
            return;
        }
        int mid = (left + right) / 2;
        if (pos <= mid) {
            update(2 * idx, left, mid, pos, value);
        } else {
            update(2 * idx + 1, mid + 1, right, pos, value);
        }
        tree[idx] = tree[2 * idx] + tree[2 * idx + 1]; // Merge results
    }

    // Query a range [l, r]
    ll query(int idx, int segLeft, int segRight, int l, int r) {
        if (r < segLeft || l > segRight) return 0; // Out of range
        if (l <= segLeft && segRight <= r) return tree[idx]; // Fully within range
        int mid = (segLeft + segRight) / 2;
        return query(2 * idx, segLeft, mid, l, r) +
               query(2 * idx + 1, mid + 1, segRight, l, r); // Merge results
    }

    // Wrapper functions for update and query
    void update(int pos, ll value) {
        update(1, 1, size, pos, value);
    }

    ll query(int l, int r) {
        return query(1, 1, size, l, r);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    // Input data
    int n;
    cin >> n;
    vector<ll> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    // Step 1: Coordinate compression
    vector<ll> sorted_nums = nums;
    sort(sorted_nums.begin(), sorted_nums.end());
    map<ll, int> coord_map; // Maps original values to compressed indices
    int compressed_idx = 1;
    for (ll val : sorted_nums) {
        if (coord_map.find(val) == coord_map.end()) {
            coord_map[val] = compressed_idx++;
        }
    }
    
    for (int i = 0 ; i < n; i++) {
        nums[i] = coord_map[nums[i]]; 
    }
    // Step 2: Initialize segment tree with compressed range
    int max_compressed = compressed_idx - 1;
    SegmentTree segTreeGreater(max_compressed);
    SegmentTree segTreeLesser(max_compressed);
    

    vector<ll> gt(n, 0 ); 
    
    for (int i = 0 ; i < n; i++) {
        int val = nums[i]; 
        gt[i] = segTreeGreater.query(val + 1, max_compressed); 
        segTreeGreater.update(val, 1);
    }
    vector<ll> lt(n , 0 ); 
    for (int i = n - 1 ; i >= 0 ; i--) {
        ll val = nums[i]; 
        lt[i] = segTreeLesser.query(1, val - 1); 
        segTreeLesser.update(val, 1);
    }
    ll res = 0;
    for (int i = 0 ; i < n; i++) {
        res += gt[i] * lt[i];
    }

    cout << res << endl;

    return 0;
}