#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Node structure
// maxsubarray sum
struct Node {
    
    long long  left;
    long long right; 
    long long max;
};
Node merge(const Node &n1, const Node &n2) {
    Node res;

    return res;
}



class SegmentTree {
private:
    vector<Node> tree; // Segment tree
    int n;

    // Build the segment tree
    void build(const vector<int> &arr, int node, int start, int end) {
        if (start == end) {
            // Leaf node: single element
            tree[node].sortedArray = {arr[start]};
            tree[node].prefix = {arr[start]};
        } else {
            int mid = (start + end) / 2;
            int leftChild = 2 * node + 1;
            int rightChild = 2 * node + 2;

            // Recursively build left and right children
            build(arr, leftChild, start, mid);
            build(arr, rightChild, mid + 1, end);

            // Merge the two child nodes
            tree[node] = merge(tree[leftChild], tree[rightChild]);
        }
    }

    // Query the sum of elements <= k in the range [L, R]
    int query(int node, int start, int end, int L, int R, int k) {
        if (start > R || end < L) {
            // No overlap
            return 0;
        }

        if (start >= L && end <= R) {
            // Full overlap: binary search on the sorted array
            auto it = upper_bound(tree[node].sortedArray.begin(), tree[node].sortedArray.end(), k);
            int idx = distance(tree[node].sortedArray.begin(), it);
            return (idx > 0) ? tree[node].prefix[idx - 1] : 0;
        }

        // Partial overlap
        int mid = (start + end) / 2;
        int leftChild = 2 * node + 1;
        int rightChild = 2 * node + 2;

        int leftResult = query(leftChild, start, mid, L, R, k);
        int rightResult = query(rightChild, mid + 1, end, L, R, k);

        return leftResult + rightResult;
    }

public:
    // Constructor
    SegmentTree(const vector<int> &arr) {
        n = arr.size();
        tree.resize(4 * n); // Allocate space for the tree
        build(arr, 0, 0, n - 1);
    }

    // Public query function
    int query(int L, int R, int k) {
        return query(0, 0, n - 1, L, R, k);
    }
};

int main() {
    vector<int> arr = {1, 3, 2, 8, 6};

    // Build the segment tree
    SegmentTree segTree(arr);

    // Query: Sum of all elements <= 5 in range [1, 4]
    cout << "Sum of elements <= 5 in range [1, 4]: " 
         << segTree.query(1, 4, 5) << endl;

    // Query: Sum of all elements <= 7 in range [0, 3]
    cout << "Sum of elements <= 7 in range [0, 3]: " 
         << segTree.query(0, 3, 7) << endl;

    return 0;
}
