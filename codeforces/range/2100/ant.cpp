#include <bits/stdc++.h>
using namespace std;

struct Node {
    int min;
    int gcd;
    int mincount;
    
    static Node merge(const Node& left, const Node& right) {
        int newmin = std::min(left.min, right.min); // Use std::min
        int newmincount = 0;
        if (left.min == newmin) {
            newmincount += left.mincount;
        }
        if (right.min == newmin) {
            newmincount += right.mincount;
        }
        int newgcd = std::gcd(left.gcd, right.gcd); // Use std::gcd
        return {newmin, newgcd, newmincount};
    }
};

int n;                 // Size of the array
vector<Node> st;       // Segment tree (1-indexed)

void build(const vector<int>& arr, int idx, int left, int right) {
    if (left == right) {
        // Initialize leaf node
        st[idx] = {arr[left], arr[left], 1};
        return;
    }
    int mid = (left + right) / 2;
    build(arr, 2 * idx, left, mid);          // Build left child
    build(arr, 2 * idx + 1, mid + 1, right); // Build right child
    st[idx] = Node::merge(st[2 * idx], st[2 * idx + 1]); // Merge results
}

// Query for range [l, r]
Node query(int idx, int segLeft, int segRight, int l, int r) {
    if (l > segRight || r < segLeft) {
        return {INT_MAX, 0, 0}; // Neutral node
    }
    if (l <= segLeft && segRight <= r) {
        return st[idx]; // Fully within range
    }
    int mid = (segLeft + segRight) / 2;
    Node leftQuery = query(2 * idx, segLeft, mid, l, r);
    Node rightQuery = query(2 * idx + 1, mid + 1, segRight, l, r);
    return Node::merge(leftQuery, rightQuery); // Merge results
}

void update(int idx, int segLeft, int segRight, int pos, int value) {
    if (segLeft == segRight) {
        // Update the leaf node
        st[idx] = {value, value, 1};
        return;
    }
    int mid = (segLeft + segRight) / 2;
    if (pos <= mid) {
        update(2 * idx, segLeft, mid, pos, value); // Update left child
    } else {
        update(2 * idx + 1, mid + 1, segRight, pos, value); // Update right child
    }
    st[idx] = Node::merge(st[2 * idx], st[2 * idx + 1]); // Recalculate node value
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    vector<int> arr(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }

    st.resize(4 * n); // Allocate space for segment tree
    
    build(arr, 1, 1, n);
    
    int m;
    cin >> m;
    while (m--) {
        int a, b;
        cin >> a >> b;

        // Call the standalone query function
        Node res = query(1, 1, n, a, b);
        if (res.gcd == res.min) {
            cout << b - a + 1 - res.mincount << endl; 
        } else {
            cout << b - a + 1 << endl; 
        }
    }

    return 0;
}
 