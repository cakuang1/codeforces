#include <bits/stdc++.h>
using namespace std;

struct SegmentTree {
    struct Node {
        long double sum = 0;  // Sum of the segment
        long double a = 1;    // Scaling factor (for linear transformation)
        long double b = 0;    // Addition factor (for linear transformation)
    };

    int n;
    vector<Node> tree;

    SegmentTree(int size) {
        n = size;
        tree.resize(4 * n);
    }

    void apply(int node, int start, int end, long double a, long double b) {
        // Apply the linear transformation (a, b) to the node
        tree[node].sum = a * tree[node].sum + b * (end - start + 1);
        tree[node].a = a * tree[node].a;
        tree[node].b = a * tree[node].b + b;
    }

    void propagate(int node, int start, int end) {
        if (tree[node].a != 1 || tree[node].b != 0) { // Check if there's a pending update
            int mid = (start + end) / 2;
            apply(2 * node, start, mid, tree[node].a, tree[node].b);       // Left child
            apply(2 * node + 1, mid + 1, end, tree[node].a, tree[node].b); // Right child
            tree[node].a = 1; // Reset lazy values
            tree[node].b = 0;
        }
    }

    void update(int node, int start, int end, int l, int r, long double a, long double b) {
        if (r < start || l > end) return; // Out of range
        if (l <= start && end <= r) {    // Fully in range
            apply(node, start, end, a, b);
            return;
        }
        propagate(node, start, end); // Propagate updates
        int mid = (start + end) / 2;
        update(2 * node, start, mid, l, r, a, b);
        update(2 * node + 1, mid + 1, end, l, r, a, b);
        tree[node].sum = tree[2 * node].sum + tree[2 * node + 1].sum; // Merge results
    }

    long double query(int node, int start, int end, int l, int r) {
        if (r < start || l > end) return 0; // Out of range
        if (l <= start && end <= r) return tree[node].sum; // Fully in range
        propagate(node, start, end); // Propagate updates
        int mid = (start + end) / 2;
        return query(2 * node, start, mid, l, r) + query(2 * node + 1, mid + 1, end, l, r);
    }

    void update_range(int l, int r, long double a, long double b) {
        update(1, 0, n - 1, l, r, a, b);
    }

    long double query_range(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }
};



int main() {
    int n, q;
    cin >> n >> q;
    SegmentTree seg(n);
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int l, r;
            long double x; // Add x to range [l, r]
            cin >> l >> r >> x;
            seg.update_range(l, r, 1, x);
        } else if (type == 2) {
            int l, r;
            long double x; // Assign x to range [l, r]
            cin >> l >> r >> x;
            seg.update_range(l, r, 0, x);
        } else if (type == 3) {
            int l, r;
            long double x; // Multiply range [l, r] by x
            cin >> l >> r >> x;
            seg.update_range(l, r, x, 0);
        } else if (type == 4) {
            int l, r; // Query sum of range [l, r]
            cin >> l >> r;
            cout << fixed << setprecision(10) << seg.query_range(l, r) << "\n";
        }
    }
    return 0;
}
 

