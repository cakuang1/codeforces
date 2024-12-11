#include <vector>
#include <iostream>
#include <climits>



class SegmentTree {
private:
    std::vector<long long> tree;    // Segment tree array
    std::vector<long long> lazy;    // Lazy propagation array
    int n;                          // Size of the input array

    // Build the tree recursively
    void build(const std::vector<int>& arr, int node, int start, int end) {
        if (start == end) {
            // Leaf node: store the value in the tree
            tree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            build(arr, 2 * node, start, mid);       // Left child
            build(arr, 2 * node + 1, mid + 1, end); // Right child
            tree[node] = tree[2 * node] + tree[2 * node + 1]; // Combine
        }
    }

    // Update a range with lazy propagation
    void updateRange(int node, int start, int end, int l, int r, int val) {
        // Handle any pending updates for this node
        if (lazy[node] != 0) {
            tree[node] += (end - start + 1) * lazy[node]; // Apply the pending update
            if (start != end) {
                lazy[2 * node] += lazy[node];       // Mark the left child as lazy
                lazy[2 * node + 1] += lazy[node];   // Mark the right child as lazy
            }
            lazy[node] = 0; // Clear the lazy value for the current node
        }

        // No overlap
        if (start > r || end < l) {
            return;
        }

        // Total overlap
        if (start >= l && end <= r) {
            tree[node] += (end - start + 1) * val; // Update the current node
            if (start != end) {
                lazy[2 * node] += val;       // Mark the left child as lazy
                lazy[2 * node + 1] += val;   // Mark the right child as lazy
            }
            return;
        }

        // Partial overlap
        int mid = (start + end) / 2;
        updateRange(2 * node, start, mid, l, r, val);       // Update left child
        updateRange(2 * node + 1, mid + 1, end, l, r, val); // Update right child
        tree[node] = tree[2 * node] + tree[2 * node + 1]; // Combine
    }

    // Query a range with lazy propagation
    long long queryRange(int node, int start, int end, int l, int r) {
        // Handle any pending updates for this node
        if (lazy[node] != 0) {
            tree[node] += (end - start + 1) * lazy[node]; // Apply the pending update
            if (start != end) {
                lazy[2 * node] += lazy[node];       // Mark the left child as lazy
                lazy[2 * node + 1] += lazy[node];   // Mark the right child as lazy
            }
            lazy[node] = 0; // Clear the lazy value for the current node
        }

        // No overlap
        if (start > r || end < l) {
            return 0;
        }

        // Total overlap
        if (start >= l && end <= r) {
            return tree[node];
        }

        // Partial overlap
        int mid = (start + end) / 2;
        long long left = queryRange(2 * node, start, mid, l, r);       // Query left child
        long long right = queryRange(2 * node + 1, mid + 1, end, l, r); // Query right child
        return left + right; // Combine
    }

public:
    // Constructor
    SegmentTree(const std::vector<int>& arr) {
        n = arr.size();
        tree.resize(4 * n, 0);
        lazy.resize(4 * n, 0);
        build(arr, 1, 0, n - 1);
    }

    // Update a range
    void update(int l, int r, int val) {
        updateRange(1, 0, n - 1, l, r, val);
    }

    // Query a range
    long long query(int l, int r) {
        return queryRange(1, 0, n - 1, l, r);
    }
};
