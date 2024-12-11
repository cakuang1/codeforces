#include <bits/stdc++.h>
using namespace std;

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
    // Example usage
    vector<int> arr = {1, 3, -2, 8, -7, 10, 5, 12};

    // Create a Sparse Table for Range Minimum Query (RMQ)
    SparseTable st_min(arr, [](int a, int b) { return min(a, b); });

    cout << "Range Minimum Queries:" << endl;
    cout << st_min.query(0, 2) << endl;  // Output: -2
    cout << st_min.query(3, 5) << endl;  // Output: -7
    cout << st_min.query(1, 7) << endl;  // Output: -7

    // Create a Sparse Table for Range Maximum Query
    SparseTable st_max(arr, [](int a, int b) { return max(a, b); });

    cout << "\nRange Maximum Queries:" << endl;
    cout << st_max.query(0, 2) << endl;  // Output: 3
    cout << st_max.query(3, 5) << endl;  // Output: 10
    cout << st_max.query(1, 7) << endl;  // Output: 12

    // Create a Sparse Table for GCD Query
    SparseTable st_gcd(arr, [](int a, int b) { return __gcd(a, b); });

    cout << "\nRange GCD Queries:" << endl;
    cout << st_gcd.query(0, 2) << endl;  // Output: 1
    cout << st_gcd.query(3, 5) << endl;  // Output: 1
    cout << st_gcd.query(1, 7) << endl;  // Output: 1

    return 0;
}
