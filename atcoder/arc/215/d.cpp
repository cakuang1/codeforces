#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

static const int MOD = 1'000'000'007;

int64 mod_pow(int64 a, int64 e) {
    int64 r = 1;
    while (e > 0) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    // A has length N+1.
    //
    // Number of odd-indexed positions:
    // 1, 3, 5, ...
    int oddCnt = N / 2 + 1;

    // Number of even-indexed positions:
    // 2, 4, 6, ...
    int evenCnt = (N + 1) / 2;

    // We need combinations up to M + max(oddCnt, evenCnt).
    int LIM = M + max(oddCnt, evenCnt);

    vector<int64> fact(LIM + 1), invFact(LIM + 1);

    fact[0] = 1;
    for (int i = 1; i <= LIM; ++i) {
        fact[i] = fact[i - 1] * i % MOD;
    }

    invFact[LIM] = mod_pow(fact[LIM], MOD - 2);

    for (int i = LIM; i >= 1; --i) {
        invFact[i - 1] = invFact[i] * i % MOD;
    }

    auto C = [&](int n, int r) -> int64 {
        if (r < 0 || r > n) return 0;

        return fact[n]
             * invFact[r] % MOD
             * invFact[n - r] % MOD;
    };

    /*
        Valid nondecreasing S means:

        S_i <= S_{i+1}

        A_i + A_{i+1} <= A_{i+1} + A_{i+2}

        so:

        A_i <= A_{i+2}

        Therefore:

        A1 <= A3 <= A5 <= ...
        A2 <= A4 <= A6 <= ...

        So odd and even positions are independently
        nondecreasing sequences in [0, M].

        But different A can produce the same S.

        For each S, choose the canonical A with minimum A1.

        Such an A satisfies:

            A1 = 0

        OR

            last even-positioned value = M.

        So count this OR with inclusion-exclusion.
    */

    // Case 1: A1 = 0.
    //
    // Remaining oddCnt-1 odd elements:
    // nondecreasing in [0, M]
    //
    // count = C(M + oddCnt - 1, oddCnt - 1)
    //
    // All evenCnt even elements:
    //
    // count = C(M + evenCnt, evenCnt)
    int64 case1 =
        C(M + oddCnt - 1, oddCnt - 1)
        * C(M + evenCnt, evenCnt) % MOD;

    // Case 2: last even element = M.
    //
    // All oddCnt odd elements arbitrary nondecreasing:
    //
    // count = C(M + oddCnt, oddCnt)
    //
    // First evenCnt-1 even elements arbitrary nondecreasing:
    //
    // count = C(M + evenCnt - 1, evenCnt - 1)
    int64 case2 =
        C(M + oddCnt, oddCnt)
        * C(M + evenCnt - 1, evenCnt - 1) % MOD;

    // Counted twice if both:
    //
    // A1 = 0
    // and
    // last even = M
    int64 both =
        C(M + oddCnt - 1, oddCnt - 1)
        * C(M + evenCnt - 1, evenCnt - 1) % MOD;

    int64 ans = (case1 + case2 - both) % MOD;

    if (ans < 0) ans += MOD;

    cout << ans << '\n';

    return 0;
}