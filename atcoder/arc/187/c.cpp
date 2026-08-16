
// wer wpsois ans wnis staet
//  we
#include <bits/stdc++.h>
using namespace std;

static const long long MOD = 998244353;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> Q(N);
    for (int &x : Q) cin >> x;

    // Every possible P' must end in N.
    if (Q[N - 1] != -1 && Q[N - 1] != N) {
        cout << 0 << '\n';
        return 0;
    }

    // If the last position is unknown, it must be N.
    if (Q[N - 1] == -1) {
        // If N was already fixed somewhere else, impossible.
        for (int i = 0; i < N - 1; i++) {
            if (Q[i] == N) {
                cout << 0 << '\n';
                return 0;
            }
        }
        Q[N - 1] = N;
    }
    // rw w wrun so son. l erpao wer
    ///w rwonc wer n we so wer
    / we
    vector<int> fixed(N + 1, 0);
    for (int x : Q) {
        if (x != -1) fixed[x] = 1;
    }

    // free[x] = x can be placed at a -1 position.
    vector<int> freeValue(N + 1, 0);
    for (int x = 1; x <= N; x++) {
        freeValue[x] = !fixed[x];
    }

    // freeLess[j] = number of free values < j.
    vector<int> freeLess(N + 1, 0);
    int cnt = 0;

    for (int j = 1; j <= N; j++) {
        freeLess[j] = cnt;
        if (freeValue[j]) cnt++;
    }
    

    // wbulw. s ortw r
    /*


        dp[j]:
        weighted number of ways to fill positions [0..i]
        such that the maximum so far is j.

        Weight = 2^(number of record maximum updates after position 1).
    */
    vector<long long> dp(N + 1), ndp(N + 1);

    int usedFree = 0;

    // ---------- First position ----------
    // The first element is NOT counted as a "maximum update",
    // so there is no factor 2 here.

    if (Q[0] != -1) {
        dp[Q[0]] = 1;
    } else {
        for (int x = 1; x <= N; x++) {
            if (freeValue[x]) {
                dp[x] = 1;
            }
        }
        usedFree = 1;
    }

    // ---------- Remaining positions ----------
    for (int i = 1; i < N; i++) {
        fill(ndp.begin(), ndp.end(), 0);

        if (Q[i] != -1) {
            int x = Q[i];

            /*
                If previous maximum j < x:
                    x becomes a new maximum
                    => factor 2.

                If j > x:
                    maximum remains j
                    => factor 1.
            */

            long long pref = 0;

            for (int j = 1; j < x; j++) {
                pref += dp[j];
                if (pref >= MOD) pref -= MOD;
            }

            ndp[x] = 2 * pref % MOD;

            for (int j = x + 1; j <= N; j++) {
                ndp[j] += dp[j];
                if (ndp[j] >= MOD) ndp[j] -= MOD;
            }
        } else {
            /*
                We choose some unused free value x.

                Two possibilities:

                1. x < current maximum j
                   Maximum remains j.

                2. x > current maximum j
                   x becomes new maximum.
                   Multiply by 2.
            */

            // Case 1: choose x < j.
            for (int j = 1; j <= N; j++) {
                if (dp[j] == 0) continue;

                /*
                    How many unused free values < j?

                    freeLess[j]
                      = total free values < j.

                    usedFree
                      = number of free values already used.

                    Since current maximum is j,
                    every used value is <= j.

                    If j itself is a free value, one of the used
                    free values is j, not < j, so add it back.
                */
                int ways = freeLess[j] - usedFree;

                if (freeValue[j]) {
                    ways++;
                }

                if (ways > 0) {
                    ndp[j] =
                        (ndp[j] + dp[j] * ways) % MOD;
                }
            }

            // Case 2: choose x > previous maximum.
            //
            // For each free x:
            // ndp[x] += 2 * sum(dp[j]) for j < x.
            long long pref = 0;

            for (int x = 1; x <= N; x++) {
                if (freeValue[x]) {
                    ndp[x] =
                        (ndp[x] + 2 * pref) % MOD;
                }

                pref += dp[x];
                if (pref >= MOD) pref -= MOD;
            }

            usedFree++;
        }

        dp.swap(ndp);
    }


    
    cout << dp[N] % MOD << '\n';

    return 0;
}


// wr1 losp bubl rs srw rw
// ww whor