#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const long long MOD = 998244353;

    int N;
    string A, B;
    cin >> N >> A >> B;

    long long x = 0, y = 0;

    for (int i = 0; i < N; i++) {
        int a = A[i] - '0';
        int b = B[i] - '0';

        int big = max(a, b);
        int small = min(a, b);

        x = (x * 10 + big) % MOD;
        y = (y * 10 + small) % MOD;
    }

    cout << x * y % MOD << '\n';
}

// wsdfwrsdwroh oshsiow