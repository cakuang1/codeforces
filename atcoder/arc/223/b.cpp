#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

constexpr int MOD = 998244353;
constexpr int MAX_N = 200000;

int64 modPow(int64 a, int64 e) {
    int64 result = 1;

    while (e > 0) {
        if (e & 1) {
            result = result * a % MOD;
        }
        a = a * a % MOD;
        e >>= 1;
    }

    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int64> fact(MAX_N + 1), invFact(MAX_N + 1);

    fact[0] = 1;
    for (int i = 1; i <= MAX_N; ++i) {
        fact[i] = fact[i - 1] * i % MOD;
    }

    invFact[MAX_N] = modPow(fact[MAX_N], MOD - 2);

    for (int i = MAX_N; i >= 1; --i) {
        invFact[i - 1] = invFact[i] * i % MOD;
    }

    auto combination = [&](int n, int k) -> int64 {
        return fact[n] * invFact[k] % MOD
             * invFact[n - k] % MOD;
    };

    int T;
    cin >> T;

    while (T--) {
        int N;
        int64 K;
        cin >> N >> K;

        vector<int64> A(N), residue(N), group(N);

        for (int i = 0; i < N; ++i) {
            cin >> A[i];

            residue[i] = A[i] % K;
            int64 complement = (K - residue[i]) % K;
            group[i] = min(residue[i], complement);
        }

        int64 answer = 1;

        for (int left = 0; left < N; ) {
            int right = left;

            while (right < N && group[right] == group[left]) {
                ++right;
            }

            int length = right - left;
            int64 r = residue[left];
            int64 complement = (K - r) % K;

            if (r != complement) {
                // Two different complementary residue classes.
                int countR = 0;

                for (int i = left; i < right; ++i) {
                    if (residue[i] == r) {
                        ++countR;
                    }
                }

                answer = answer * combination(length, countR) % MOD;
            } else {
                // Self-complementary residue: arbitrary permutation.
                unordered_map<int64, int> frequency;

                for (int i = left; i < right; ++i) {
                    ++frequency[A[i]];
                }

                int64 ways = fact[length];

                for (auto [value, count] : frequency) {
                    ways = ways * invFact[count] % MOD;
                }

                answer = answer * ways % MOD;
            }

            left = right;
        }

        cout << answer << '\n';
    }
}