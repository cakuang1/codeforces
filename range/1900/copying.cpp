#include <bits/stdc++.h>
using namespace std;
using ll = long long;

class SegmentTree {
public:
    vector<long long> tree;   // Segment tree array
    vector<long long> lazy;   // Lazy array for deferred updates
    int n;

    SegmentTree(int size) {
        n = size;
        tree.assign(4 * n, 0);
        lazy.assign(4 * n, 0);
    }
    
    // Propagate lazy updates to children
    void propagate(int node, int start, int end) {
        if (lazy[node] != 0) {
            // Apply the lazy value to the current node
            tree[node] = lazy[node]; // Set node value to the lazy value

            // If not a leaf node, propagate to children
            if (start != end) {
                lazy[2 * node] = lazy[node];
                lazy[2 * node + 1] = lazy[node];
            }

            // Clear the lazy value for the current node
            lazy[node] = 0;
        }
    }

    // Range update: Set a range [l, r] to `value`
    void update(int node, int start, int end, int l, int r, long long value) {
        propagate(node, start, end); // Ensure current node is up-to-date

        if (start > r || end < l) {
            return; // Out of range
        }

        if (start >= l && end <= r) {
            // Fully within range
            lazy[node] = value;
            propagate(node, start, end);
            return;
        }

        int mid = (start + end) / 2;
        update(2 * node, start, mid, l, r, value);
        update(2 * node + 1, mid + 1, end, l, r, value);

        // Merge results (no need here as the value is set directly in the propagate step)
    }

    // Point query: Get the value at position `idx`
    long long query(int node, int start, int end, int idx) {
        propagate(node, start, end); // Ensure current node is up-to-date

        if (start == end) {
            return tree[node]; // Leaf node
        }

        int mid = (start + end) / 2;
        if (idx <= mid) {
            return query(2 * node, start, mid, idx);
        } else {
            return query(2 * node + 1, mid + 1, end, idx);
        }
    }

    // Wrapper for range update
    void update(int l, int r, long long value) {
        update(1, 1, n, l, r, value);
    }

    // Wrapper for point query
    long long query(int idx) {
        return query(1, 1, n, idx);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<ll> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
    }

    SegmentTree segTree(n);
    vector<tuple<int, int, int>> typeOnes; // Store type 1 queries

    int curr = 1; // Unique identifier for each copy operation
    // whats the offset 
    while (m--) {
        int type;
        cin >> type;

        if (type == 1) {
            // Copy operation
            int x, y, k;
            cin >> x >> y >> k;

            segTree.update(y, y + k - 1, curr);
            typeOnes.push_back({x, y, k});
            curr++;
        } else if (type == 2) {
            // Value retrieval
            int x;
            cin >> x;

            long long val = segTree.query(x);
            if (val == 0) {
                // No copy operation affects this position
                cout << b[x] << "\n";
            } else {
                // Resolve the value from array `a`
                auto [startA, startB, len] = typeOnes[val - 1];
                int offset = x - startB;
                cout << a[startA + offset] << "\n";
            }
        }
    }
    // 
    return 0;
}
