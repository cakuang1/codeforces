#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int INF = 1e9 + 10;

struct SegmentTree {
    vector<int> tree;
    int size;

    SegmentTree(int n) {
        size = n;
        tree.assign(4 * n, INF); // Initialize segment tree with INF for minimum query
    }

    void update(int index, int value, int node, int start, int end) {
        if (start == end) {
            tree[node] = min(tree[node], value); // Update the minimum value at the leaf
        } else {
            int mid = (start + end) / 2;
            if (index <= mid) {
                update(index, value, 2 * node + 1, start, mid);
            } else {
                update(index, value, 2 * node + 2, mid + 1, end);
            }
            tree[node] = min(tree[2 * node + 1], tree[2 * node + 2]); // Update parent node
        }
    }

    int query(int l, int r, int node, int start, int end) {
        if (r < start || l > end) return INF; // Out of range
        if (l <= start && end <= r) return tree[node]; // Fully within range

        int mid = (start + end) / 2;
        return min(query(l, r, 2 * node + 1, start, mid),
                   query(l, r, 2 * node + 2, mid + 1, end));
    }

    void update(int index, int value) {
        update(index, value, 0, 0, size - 1);
    }

    int query(int l, int r) {
        return query(l, r, 0, 0, size - 1);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<vector<int>> boxes(n);
    vector<int> list;

    // Input and flatten all dimensions
    for (int i = 0; i < n; i++) {
        vector<int> d(3);
        for (int j = 0; j < 3; j++) {
            cin >> d[j];
            list.push_back(d[j]);
        }
        boxes[i] = d;
    }

    // Coordinate compression
    int curr = 1;
    map<int, int> m;
    sort(list.begin(), list.end());
    for (int i = 0; i < list.size(); i++) {
        if (m.find(list[i]) == m.end()) {
            m[list[i]] = curr++;
        }
    }

    // Compress box dimensions and sort dimensions for rotations
    for (int i = 0; i < n; i++) {
        sort(boxes[i].begin(), boxes[i].end()); // Ensure [small, medium, large]
        for (int j = 0; j < 3; j++) {
            boxes[i][j] = m[boxes[i][j]];
        }
    }

    // Sort boxes by first dimension ascending, second dimension descending
    sort(boxes.begin(), boxes.end(), [](const auto& b1, const auto& b2) {
        if (b1[0] != b2[0]) return b1[0] < b2[0];
        return b1[1] > b2[1];
    });

    // Use a segment tree for the third dimension
    SegmentTree segTree(curr);

    for (const auto& box : boxes) {
        int w = box[1], d = box[2];

        // Query the segment tree for the minimum value in range [0, w - 1]
        if (w > 0 && segTree.query(0, w - 1) < d) {
            cout << "Yes\n";
            return 0;
        }

        // Update the segment tree at index `w` with `d`
        segTree.update(w, d);
    }

    cout << "No\n";
    return 0;
}


