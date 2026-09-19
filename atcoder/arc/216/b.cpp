#include <bits/stdc++.h>
using namespace std;

static const int MOD = 998244353;
static const int INF = 1e9;

long long modpow(long long a, long long e) {
    long long r = 1;
    while (e) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;

    vector<int> A(N + 1);
    vector<int> usedValue(N, 0);

    int K = 0; // total number of -1 positions

    for (int i = 1; i <= N; i++) {
        cin >> A[i];
        if (A[i] == -1) {
            K++;
        } else {
            usedValue[A[i]] = 1;
        }
    }

    // ------------------------------------------------------------
    // factorials / inverse factorials
    // ------------------------------------------------------------

    vector<long long> fact(N + 1), ifact(N + 1);

    fact[0] = 1;
    for (int i = 1; i <= N; i++) {
        fact[i] = fact[i - 1] * i % MOD;
    }

    ifact[N] = modpow(fact[N], MOD - 2);
    for (int i = N; i >= 1; i--) {
        ifact[i - 1] = ifact[i] * i % MOD;
    }

    auto C = [&](int n, int r) -> long long {
        if (r < 0 || r > n) return 0;
        return fact[n] * ifact[r] % MOD * ifact[n - r] % MOD;
    };

    // ------------------------------------------------------------
    // S = values that are not already fixed somewhere.
    //
    // G[x] = number of values v in S such that v >= x.
    // ------------------------------------------------------------

    vector<int> G(N + 1, 0);

    // G[N] = 0 because values only go up to N-1
    for (int x = N - 1; x >= 0; x--) {
        G[x] = G[x + 1] + (!usedValue[x]);
    }

    // ------------------------------------------------------------
    // F[c][m]
    //
    // F[c][m] =
    //   sum over all c-element subsets T of S of
    //   min(m, min(T)).
    //
    // recurrence:
    //
    // F[c][m+1] =
    // F[c][m] + C(G[m+1], c)
    //
    // for c >= 1.
    // ------------------------------------------------------------

    vector<vector<int>> F(K + 1, vector<int>(N + 1, 0));

    for (int c = 1; c <= K; c++) {
        for (int m = 0; m < N; m++) {
            long long add = C(G[m + 1], c);

            F[c][m + 1] = (F[c][m] + add) % MOD;
        }
    }

    // ------------------------------------------------------------
    // Prefix count of unknown positions.
    // lets us get number of -1's inside [l,r].
    // ------------------------------------------------------------

    vector<int> prefUnknown(N + 1, 0);

    for (int i = 1; i <= N; i++) {
        prefUnknown[i] =
            prefUnknown[i - 1] + (A[i] == -1);
    }

    // ------------------------------------------------------------
    // prefMin[i] = smallest fixed A[j], j <= i
    // sufMin[i]  = smallest fixed A[j], j >= i
    //
    // Ignore -1 positions.
    // ------------------------------------------------------------

    vector<int> prefMin(N + 2, INF);
    vector<int> sufMin(N + 2, INF);

    for (int i = 1; i <= N; i++) {
        prefMin[i] = prefMin[i - 1];

        if (A[i] != -1) {
            prefMin[i] = min(prefMin[i], A[i]);
        }
    }

    for (int i = N; i >= 1; i--) {
        sufMin[i] = sufMin[i + 1];

        if (A[i] != -1) {
            sufMin[i] = min(sufMin[i], A[i]);
        }
    }

    // ------------------------------------------------------------
    // Queries
    // ------------------------------------------------------------

    while (Q--) {
        int l, r;
        cin >> l >> r;

        // d = # unknown positions inside
        int d = prefUnknown[r] - prefUnknown[l - 1];

        // c = # unknown positions outside
        int c = K - d;

        // m = minimum fixed value outside
        int m = min(prefMin[l - 1], sufMin[r + 1]);

        // If there is no fixed value outside,
        // pretend m = N.
        if (m == INF) m = N;

        long long ans;

        if (c == 0) {
            /*
                No unknown positions outside.

                Therefore the smallest value outside is simply m,
                regardless of how the K unknown values are arranged
                inside.

                There are K! completions.
            */

            ans = 1LL * m * fact[K] % MOD;
        } else {
            /*
                F[c][m]:
                    sum contribution over choices of WHICH c
                    missing values go outside.

                c!:
                    arrange those chosen values among outside
                    unknown positions.

                d!:
                    arrange remaining values among inside
                    unknown positions.
            */

            ans = F[c][m];
            ans = ans * fact[c] % MOD;
            ans = ans * fact[d] % MOD;
        }

        cout << ans << '\n';
    }

    return 0;
}


