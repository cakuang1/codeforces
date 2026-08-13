#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

constexpr int64 MOD = 998244353;

int64 mod_pow(int64 base, int64 exponent) {
    int64 result = 1;

    while (exponent > 0) {
        if (exponent & 1) {
            result = result * base % MOD;
        }

        base = base * base % MOD;
        exponent >>= 1;
    }

    return result;
}

int64 mod_inverse(int64 value) {
    return mod_pow(value, MOD - 2);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    int64 invN = mod_inverse(N);

    // A_next = A[i + 1]
    // B_next = B[i + 1]
    int64 A_next = 0;
    int64 B_next = 0;

    for (int i = N - 1; i >= 0; --i) {
        int64 p = static_cast<int64>(i) * invN % MOD;
        int64 q = static_cast<int64>(N - i) * invN % MOD;

        // A_i = (p + p*q*A_{i+1} + q*B_{i+1}) / (1 - p^2)
        int64 numerator = p;
        numerator += p * q % MOD * A_next % MOD;
        numerator %= MOD;
        numerator += q * B_next % MOD;
        numerator %= MOD;

        int64 denominator = (1 - p * p % MOD + MOD) % MOD;

        int64 A_current =
            numerator * mod_inverse(denominator) % MOD;

        // B_i = p*A_i + q*A_{i+1}
        int64 B_current =
            (p * A_current + q * A_next) % MOD;

        A_next = A_current;
        B_next = B_current;
    }

    // After the loop:
    cout << A_next << ' ' << B_next << '\n';
}