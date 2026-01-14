#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MOD = 1e9 + 7; // Modulo for operations
const int N = 2;         // Dimension of the square matrix

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
                    res.mat[i][j] = (res.mat[i][j] + mat[i][k] * other.mat[k][j]) % MOD;
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
                res[i] = (res[i] + mat[i][j] * vec[j]) % MOD;
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


// Example: Solve DP using Matrix Multiplication
int main() {
    ll n;
    cin >> n; // Number of steps or transitions

    // Define Transition Matrix
    Matrix T(N);
    T.mat = {{1, 1},
             {1, 0}};

    // Define the starting vector (e.g., base case for Fibonacci)
    vector<ll> start = {1, 0}; // F(1) = 1, F(0) = 0

    // Solve for T^n (n-th transition)
    Matrix result = matPow(T, n);

    // Multiply the resulting matrix with the starting vector
    vector<ll> finalVector = result * start;

    // Output the first element as the answer (e.g., Fibonacci number F(n))
    cout << finalVector[0] << endl;

    return 0;
}
