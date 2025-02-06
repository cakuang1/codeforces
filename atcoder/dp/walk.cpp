#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int MOD = 1000000007;
const int MAXN = 50;

int N, K;
vector<vector<ll>> adj;

// Function to multiply two matrices under modulo
vector<vector<ll>> multiply(const vector<vector<ll>> &A, const vector<vector<ll>> &B) {
    vector<vector<ll>> C(N, vector<ll>(N, 0));
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
            }
        }
    }
    return C;
}

// Function to compute A^exp using binary exponentiation
vector<vector<ll>> matrix_exponentiate(vector<vector<ll>> A, ll exp) {
    vector<vector<ll>> res(N, vector<ll>(N, 0));

    // Initialize res as identity matrix
    for (int i = 0; i < N; i++) {
        res[i][i] = 1;
    }

    while (exp > 0) {
        if (exp % 2 == 1) {
            res = multiply(res, A);
        }
        A = multiply(A, A);
        exp /= 2;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    cin >> N >> K;
    adj.assign(N, vector<ll>(N));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> adj[i][j];
        }
    }

    // Compute A^K
    vector<vector<ll>> result = matrix_exponentiate(adj, K);

    // Compute total number of paths of length K
    ll totalPaths = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            totalPaths = (totalPaths + result[i][j]) % MOD;
        }
    }

    cout << totalPaths << endl;
    return 0;
}
