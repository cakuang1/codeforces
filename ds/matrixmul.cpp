#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1e9 + 7;

// Multiply two matrices
vector<vector<long long>> multiply(const vector<vector<long long>>& a, const vector<vector<long long>>& b) {
    int n = a.size();
    vector<vector<long long>> c(n, vector<long long>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % MOD;
            }
        }
    }
    return c;
}

// Matrix exponentiation
vector<vector<long long>> matrixExp(vector<vector<long long>> a, long long p) {
    int n = a.size();
    vector<vector<long long>> res(n, vector<long long>(n, 0));
    for (int i = 0; i < n; i++) res[i][i] = 1; // Identity matrix
    while (p) {
        if (p % 2) res = multiply(res, a);
        a = multiply(a, a);
        p /= 2;
    }
    return res;
}


vector<long long> multiplyMatrixVector(const vector<vector<long long>>& mat, const vector<long long>& vec) {
    int n = mat.size();
    vector<long long> result(n, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i] = (result[i] + mat[i][j] * vec[j]) % MOD;
        }
    }
    return result;
}






// contriubution weto the current stat wsi what we  

// how to see this we we  


// is there wseomthin  w 