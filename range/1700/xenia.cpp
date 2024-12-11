#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int MAX = 1 << 17; // Maximum size for 2^n elements
int tree[4 * MAX];
int n, m;

// Build the segment tree
void build(vector<int>& a, int node, int start, int end, bool isOr) {
    if (start == end) {
        // Leaf node
        tree[node] = a[start];
    } else {
        int mid = (start + end) / 2;
        // Build left and right children
        build(a, 2 * node, start, mid, !isOr);       // Alternate operation
        build(a, 2 * node + 1, mid + 1, end, !isOr);

        // Perform operation based on current level
        if (isOr) {
            tree[node] = tree[2 * node] | tree[2 * node + 1];
        } else {
            tree[node] = tree[2 * node] ^ tree[2 * node + 1];
        }
    }
}

// update the nw what w wew
void update(int node, int start, int end, int idx, int value, bool isOr) {
    if (start == end) {
        // Update the leaf node
        tree[node] = value;
    } else {
        int mid = (start + end) / 2;
        if (idx <= mid) {
            // Update in the left child
            update(2 * node, start, mid, idx, value, !isOr);
        } else {
            // Update in the right child
            update(2 * node + 1, mid + 1, end, idx, value, !isOr);
        }

        // Recalculate current node based on the current level
        if (isOr) {
            tree[node] = tree[2 * node] | tree[2 * node + 1];
        } else {
            tree[node] = tree[2 * node] ^ tree[2 * node + 1];
        }
    }
}


// thisony lwword oon wenture
int main() {
    cin >> n >> m;
    int size = 1 << n; // 2^n elements
    vector<int> a(size);

    for (int i = 0; i < size; i++) {
        cin >> a[i];
    }

    // Build the segment tree; isOr depends on whether n is odd or even
    bool isOr = (n % 2 == 1);
    build(a, 1, 0, size - 1, isOr);

    // Process queries
    for (int i = 0; i < m; i++) {
        int p, b;
        cin >> p >> b;
        p--; // Convert to 0-based index
        update(1, 0, size - 1, p, b, isOr);
        cout << tree[1] << endl; // Output the root value
    }

    return 0;
}
