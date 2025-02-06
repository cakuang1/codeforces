#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll mod = 1e9 + 7; // Default modulo
const ll mod2 = 998244353; 
const int N = 2e5 + 10; // Adjust size as needed
const ll p = 31;        // Base for hashing


struct Node {
    vector<long long> sortedArray; // Sorted elements in the range
    vector<long long> prefix;      // Prefix sum array for the sorted elements

    Node() : sortedArray(), prefix() {}
};

// Merge function to combine two nodes
Node merge(const Node &n1, const Node &n2) {
    Node res;
    int n = n1.sortedArray.size() + n2.sortedArray.size();
    res.sortedArray.resize(n);
    res.prefix.resize(n);

    // Merge sorted arrays from n1 and n2 into res
    merge(n1.sortedArray.begin(), n1.sortedArray.end(),
          n2.sortedArray.begin(), n2.sortedArray.end(),
          res.sortedArray.begin());

    // Build the prefix sum array for the merged sorted array
    res.prefix[0] = res.sortedArray[0];
    for (int i = 1; i < n; i++) {
        res.prefix[i] = res.sortedArray[i] + res.prefix[i - 1];
    }
    return res;
}

class SegmentTree {
private:
    vector<Node> tree; // Segment tree
    int n;

    // Build the segment tree
    void build(const vector<long long> &arr, int node, int start, int end) {
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
    long long query(int node, int start, int end, int L, int R, long long k) {
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

        long long leftResult = query(leftChild, start, mid, L, R, k);
        long long rightResult = query(rightChild, mid + 1, end, L, R, k);

        return leftResult + rightResult;
    }

public:
    // Constructor
    SegmentTree(const vector<long long> &arr) {
        n = arr.size();
        tree.resize(4 * n); // Allocate space for the tree
        build(arr, 0, 0, n - 1);
    }

    // Public query function
    long long query(int L, int R, long long k) {
        return query(0, 0, n - 1, L, R, k);
    }
};







// Precompute factorials and inverse factorials for combinatorial calculations
vector<ll> fact(N), invFact(N);



// take the modular inverse 

ll power(ll a, ll b) {
    ll result = 1;
    while (b > 0) {
        if (b & 1) { // If b is odd, multiply the current base to the result
            result *= a;
        }
        a *= a;      // Square the base
        b >>= 1;     // Divide b by 2
    }
    return result;
}

ll mod_inverse(ll n, ll m = mod)  {
    return power(n, m - 2);
} 

// maximum possible values w


ll modExp(ll x, ll y, ll m = mod) {
    ll res = 1;
    x = x % m;
    while (y > 0) {
        if (y & 1) {
            res = (res * x) % m;
        }
        y = y >> 1;
        x = (x * x) % m;
    }
    return res;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    ll n; cin >> n;
    vector<ll> nums(n);
    for (int i = 0 ; i < n; i ++){
         cin >> nums[i]; 
    }
    
    SegmentTree st(nums); 
    ll q; cin >> q;
    ll prev = 0;
    vector<ll> res;
    while (q --) {
        ll a , b, c; cin >> a >> b >> c;
        a = (a ^ prev);
        b = (b ^ prev);
        c = (c ^ prev);
        a --;
        b --;

        ll ans = st.query(a,b,c); 
        res.push_back(ans);
        prev = ans;        
    }
     
    for (int i = 0 ; i < res.size(); i ++) {
        cout <<  res[i] << endl; 
    }

     return 0;
}


