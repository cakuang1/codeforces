    #include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

using ll = long long;
using ld = long double;
const ll mod = 1e9 + 7; // Change as per the problem requirements
const int N = 2e5 + 10; // Adjust the size as needed

// Precompute factorials and inverse factorials for combinatorial calculations
vector<ll> fact(N);
vector<ll> invFact(N);

// Function to compute x^y % mod using binary exponentiation
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

// Function to precompute factorials and their modular inverses
void precomputeFactorials(int n) {
    fact[0] = 1;
    for (int i = 1; i <= n; i++) {
        fact[i] = (fact[i - 1] * i) % mod;
    }
    invFact[n] = modExp(fact[n], mod - 2); // Fermat's Little Theorem for modular inverse
    for (int i = n - 1; i >= 0; i--) {
        invFact[i] = (invFact[i + 1] * (i + 1)) % mod;
    }
}


// w
// Function to calculate nCr % mod
ll nCr(int n, int r) {
    if (r > n || r < 0) return 0;
    return (fact[n] * invFact[r] % mod) * invFact[n - r] % mod;
}

// Function to calculate nPr % mod
ll nPr(int n, int r) {
    if (r > n || r < 0) return 0;
    return (fact[n] * invFact[n - r]) % mod;
}

// Function to compute x^y % mod using binary exponentiation
long long binaryExp(long long x, long long y, long long mod) {
    long long result = 1;
    x = x % mod; // Handle large x

    while (y > 0) {
        if (y & 1) { // If y is odd, multiply x with the result
            result = (result * x) % mod;
        }
        y = y >> 1; // Divide y by 2
        x = (x * x) % mod; // Square x
    }
    return result;
}


// min count  wuis whta at    
struct Node {
    int min ;
    int gcd ;
    int mincount ;
    static Node merge(const Node& left, const Node& right) {
        int t = min(left.leftbrackets, right.rightbrackets);
        int newmax = left.max + right.max + t;
        int newleft = left.leftbrackets + right.leftbrackets - t;
        int newright = left.rightbrackets + right.rightbrackets - t;
        return {newmax, newleft, newright};
    }
};

// Global variables
int n;                 // Size of the array
vector<Node> st;       // Segment tree (1-indexed)

// Build the segment tree
void build(const vector<char>& arr, int idx, int left, int right) {
    if (left == right) {
        // Initialize leaf nodes based on the bracket
        if (arr[left] == '(') {
            st[idx] = {0, 1, 0}; // 1 left bracket
        } else {
            st[idx] = {0, 0, 1}; // 1 right bracket
        }
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
        return {0, 0, 0}; // Neutral values
    }
    if (l <= segLeft && segRight <= r) {
        return st[idx]; // Fully within range
    }
    int mid = (segLeft + segRight) / 2;
    Node leftQuery = query(2 * idx, segLeft, mid, l, r);
    Node rightQuery = query(2 * idx + 1, mid + 1, segRight, l, r);
    return Node::merge(leftQuery, rightQuery); // Merge results
}

// Update a single point
void update(int idx, int segLeft, int segRight, int pos, char value) {
    if (segLeft == segRight) {
        // Update the leaf node
        if (value == '(') {
            st[idx] = {0, 1, 0};
        } else {
            st[idx] = {0, 0, 1};
        }
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
    string s;
    cin >> s; 
    n = s.size();
    vector<char> arr(n + 1);
    for (int i = 1; i <= n; i++) {
        arr[i] = s[i - 1];
    }

    st.resize(4 * n); 
    build(arr, 1, 1, n);
    int m; 
    cin >> m;
    for (int i = 0 ; i < m; i++) {
        int a , b;
        cin >> a >> b; 
        cout << query(1,1,n, a, b).max * 2 << endl; 
    } 
    
    // the gcd of the  

    // how to do you see 
       
    return 0;
}