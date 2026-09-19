#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

static const int64 MOD = 998244353;

int64 mod_pow(int64 a, long long e) {
    int64 r = 1;
    while (e > 0) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

struct Fenwick {
    int n;
    vector<int> bit;

    Fenwick(int n) : n(n), bit(n + 1, 0) {}

    void add(int x, int v) {
        for (; x <= n; x += x & -x)
            bit[x] += v;
    }

    int sum(int x) const {
        int res = 0;
        for (; x > 0; x -= x & -x)
            res += bit[x];
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;

    vector<int> P(N + 1);
    for (int i = 1; i <= N; i++) {
        cin >> P[i];
    }

    // ------------------------------------------------------------
    // Compute I0 = inversion count of initial P.
    // ------------------------------------------------------------
    Fenwick fw(N);

    int64 I0 = 0;

    for (int i = 1; i <= N; i++) {
        int le = fw.sum(P[i]);
        I0 += (i - 1) - le;
        fw.add(P[i], 1);
    }

    // ------------------------------------------------------------
    // Compute S = sum of inversion counts over all N cyclic shifts.
    //
    // If I_s = inversion count after right shift by s,
    //
    // I_{s+1} - I_s = 2 * P[N-s] - (N+1)
    // ------------------------------------------------------------
    int64 cur = I0;
    int64 S = I0;

    for (int s = 0; s < N - 1; s++) {
        int x = P[N - s];

        cur += 2LL * x - (N + 1);
        S += cur;
    }

    int64 invN = mod_pow(N, MOD - 2);

    int64 C2 = 1LL * N * (N - 1) / 2 % MOD;

    while (Q--) {
        int x;
        long long K;

        cin >> x >> K;

        int a = P[x];
        int b = P[x + 1];

        // --------------------------------------------------------
        // Adjacent swap changes I0 by only +/-1.
        // --------------------------------------------------------
        int64 deltaI;

        if (a < b) {
            // non-inversion becomes inversion
            deltaI = 1;
        } else {
            // inversion becomes non-inversion
            deltaI = -1;
        }

        /*
            S = N * I0 + sum d_s,
            where d_s = I_s - I0.

            Swapping adjacent values a,b only changes one d_s,
            by 2(a-b).

            Therefore:
                delta S = N * deltaI + 2(a-b)
        */
        S += 1LL * N * deltaI + 2LL * (a - b);
        I0 += deltaI;

        swap(P[x], P[x + 1]);

        // --------------------------------------------------------
        // total number of operation sequences
        // --------------------------------------------------------
        int64 total = mod_pow(N - 1, K);

        /*
            dp shift counts:

            a_0 = v + (-1)^K
            a_s = v, s != 0

            Therefore:

            v = ((N-1)^K - (-1)^K) / N
        */
        int64 sign;

        if (K % 2 == 0)
            sign = 1;
        else
            sign = MOD - 1; // -1 mod MOD

        int64 v = (total - sign + MOD) % MOD;
        v = v * invN % MOD;

        int64 i0 = (I0 % MOD + MOD) % MOD;
        int64 ssum = (S % MOD + MOD) % MOD;

        /*
            Before handling the final reversal:

            weighted inversion sum =
                (-1)^K * I0 + v * S
        */
        int64 W = sign * i0 % MOD;
        W = (W + v * ssum) % MOD;

        int64 ans;

        if (K % 2 == 0) {
            // No final reversal remains.
            ans = W;
        } else {
            /*
                For any permutation q:

                inv(reverse(q)) = C(N,2) - inv(q)

                There are total = (N-1)^K sequences.
            */
            ans = total * C2 % MOD;
            ans = (ans - W + MOD) % MOD;
        }

        cout << ans << '\n';
    }

    return 0;
}

//  youw erewro wer