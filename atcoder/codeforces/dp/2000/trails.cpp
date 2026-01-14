#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll mod = 1e9 + 7; // Default modulo
const int N = 2e5 + 10; // Adjust size as needed
const ll p = 31;        // Base for hashing

// Matrix Structure
struct Matrix {
    vector<vector<ll>> mat;
    int n;

    Matrix(int size) : n(size) {
        mat.assign(n, vector<ll>(n, 0));
    }

    // Identity matrix
    static Matrix identity(int size) {
        Matrix I(size);
        for (int i = 0; i < size; i++)
            I.mat[i][i] = 1;
        return I;
    }

    // Overload * operator for matrix multiplication
    Matrix operator*(const Matrix &other) const {
        Matrix res(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                res.mat[i][j] = 0;
                for (int k = 0; k < n; k++) {
                    res.mat[i][j] = (res.mat[i][j] + mat[i][k] * other.mat[k][j]) % mod;
                }
            }
        }
        return res;
    }

    // Multiply matrix with a vector
    vector<ll> operator*(const vector<ll> &vec) const {
        vector<ll> res(n, 0);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                res[i] = (res[i] + mat[i][j] * vec[j]) % mod;
            }
        }
        return res;
    }
};

// Matrix Exponentiation
Matrix matPow(Matrix base, ll exp) {
    Matrix res = Matrix::identity(base.n); // Start with identity matrix
    while (exp) {
        if (exp % 2 == 1)
            res = res * base; // Multiply if exponent is odd
        base = base * base;   // Square the base
        exp /= 2;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int m, n;
    cin >> m >> n; // m = matrix size, n = exponent (e.g., steps or transitions)

    vector<int> s(m), l(m);
    for (int i = 0; i < m; i++) cin >> s[i];
    for (int i = 0; i < m; i++) cin >> l[i];

    // Initialize the transition matrix
    Matrix T(m);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            T.mat[i][j] = (1LL * s[i] * s[j] + 1LL * s[i] * l[j] + 1LL * l[i] * s[j]) % mod;
        }
    }

    // Starting vector
    vector<ll> start(m, 0);
    start[0] = 1; // First element initialized to 1

    // Exponentiate the matrix and apply it to the starting vector
    Matrix resMatrix = matPow(T, n);
    vector<ll> finalVector = resMatrix * start;

    // Calculate the final result
    ll finalResult = 0;
    for (ll k : finalVector) {
        finalResult = (finalResult + k) % mod;
    }

    cout << finalResult << endl;

    return 0;
}
