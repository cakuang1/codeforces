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

// Dynamic Sparse Table class
class SparseTable {
private:
    vector<vector<int>> sparse_table;
    vector<int> log_values;
    int n;

    function<int(int, int)> combine;  // Function to combine two values

public:
    // Constructor takes an array and a combining function (like min, max, gcd, etc.)
    SparseTable(const vector<int>& arr, function<int(int, int)> combineFunction) {
        n = arr.size();
        int LOG = log2(n) + 1;
        combine = combineFunction;

        // Resize the sparse table
        sparse_table.resize(n, vector<int>(LOG));

        // Initialize log values for each index up to n
        log_values.resize(n + 1);
        log_values[1] = 0;
        for (int i = 2; i <= n; i++) {
            log_values[i] = log_values[i / 2] + 1;
        }

        // Build the Sparse Table
        // Fill the first level with the original array values
        for (int i = 0; i < n; i++) {
            sparse_table[i][0] = arr[i];
        }

        // Fill the rest of the Sparse Table using the given combining function
        for (int j = 1; (1 << j) <= n; j++) {
            for (int i = 0; (i + (1 << j) - 1) < n; i++) {
                sparse_table[i][j] = combine(sparse_table[i][j - 1], sparse_table[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    int query(int L, int R) {
        // Find the largest power of 2 that fits in the length of the range
        int length = R - L + 1;
        int k = log_values[length];
        return combine(sparse_table[L][k], sparse_table[R - (1 << k) + 1][k]);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    precomputeFactorials(N - 1);

    ll n; 
    cin >> n;
    vector<int> nums(n); 
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    SparseTable gcdtable(nums, [](int a, int b) { return __gcd(a, b); });

    int maxrange = 0;
    set<int> s; 

    for (int i = 0; i < n; i++) {
        // how to see tshi we we we

        // reduce optoin incraisng reisks w 

        int val = nums[i];


        int leftbound = i;


        int left = 0 , right = i ;


        while (left <= right) {
            int mid = left + (right - left)/2;
            if (gcdtable.query(mid , i ) == val) {
                leftbound = mid; 
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }     

        
        

        left = i;
        right = n - 1; 
        int rightbound = i;
        while (left <= right) {
            int mid = left + (right - left)/2;
            if (gcdtable.query(i , mid ) == val) {
                rightbound = mid; 
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        

        if (rightbound - leftbound >= maxrange) {
            if (rightbound - leftbound == maxrange) {
                s.insert(leftbound);
            } else {
                maxrange = rightbound - leftbound;
                s.clear();
                s.insert(leftbound);
            }
        }
    }
    cout << s.size() << " " << maxrange << endl;
    for (auto it = s.begin() ; it != s.end() ; it ++) {
        cout << *it  + 1 << " ";  // Print 1-based index
    }

    cout << endl;

    return 0;
}
