#include <bits/stdc++.h>
using namespace std;

static const long long MOD = 1'000'000'007LL;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> A(N);
    for (int &x : A) cin >> x;

    // Any prefix sum is in [-10N, 10N].
    const int B = 10 * N;
    const int OFF = B;
    const int W = 2 * B + 1;

    vector<vector<long long>> dp(N, vector<long long>(W));

    /*
        Initialization:

        Suppose i is the first position that visibly changes.

        Before i, everything must remain equal to the original array.
        We can choose some p < i as the previous selected element.

        Then:
            A[i] -> A[i] + A[p]

        so j = A[p].

        Equal A[p]'s produce the same resulting array, so only count
        each distinct nonzero value once.
    */
    for (int i = 0; i < N; ++i) {
        set<int> seen;

        for (int p = 0; p < i; ++p) {
            if (A[p] != 0)
                seen.insert(A[p]);
        }

        for (int v : seen) {
            dp[i][v + OFF] = 1;
        }
    }

    for (int i = 0; i < N; ++i) {
        for (int idx = 0; idx < W; ++idx) {
            long long ways = dp[i][idx];
            if (ways == 0) continue;

            int j = idx - OFF;

            // Current cumulative sum after selecting i.
            int sum = A[i] + j;

            if (sum != 0) {
                /*
                    Normal case.

                    If k is the next selected position, then:

                        A[k] -> A[k] + sum

                    Since sum != 0, k visibly changes.

                    Therefore new j = sum.
                */
                for (int k = i + 1; k < N; ++k) {
                    dp[k][sum + OFF] += ways;

                    if (dp[k][sum + OFF] >= MOD)
                        dp[k][sum + OFF] -= MOD;
                }
            } else {
                /*
                    Special case: cumulative sum is currently 0.

                    Suppose k is the next visibly changed position.

                    We need to select some p with

                        i < p < k

                    first.

                    Since current sum is 0:

                        A[p] -> A[p]

                    so p is invisible.

                    But now the cumulative sum becomes A[p].

                    Then selecting k gives

                        A[k] -> A[k] + A[p]

                    Hence new j = A[p].

                    Equal A[p] values must be deduplicated.
                */
                set<int> seen;

                for (int k = i + 1; k < N; ++k) {
                    // seen currently contains exactly
                    // distinct A[p] with i < p < k.
                    for (int v : seen) {
                        dp[k][v + OFF] += ways;

                        if (dp[k][v + OFF] >= MOD)
                            dp[k][v + OFF] -= MOD;
                    }

                    // This position can become p for future k's.
                    if (A[k] != 0)
                        seen.insert(A[k]);
                }
            }
        }
    }

    /*
        Every changed resulting array has a unique last visibly
        changed position i and nonzero change j, so sum all states.

        +1 is the completely unchanged array.
        For example, choosing a subsequence of length 1 always leaves
        the array unchanged.
    */
    long long ans = 1;

    for (int i = 0; i < N; ++i) {
        for (int idx = 0; idx < W; ++idx) {
            ans += dp[i][idx];
            ans %= MOD;
        }
    }

    cout << ans << '\n';
}