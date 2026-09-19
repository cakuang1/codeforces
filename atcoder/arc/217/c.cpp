#include <bits/stdc++.h>
using namespace std;

using ll = long long;

static const ll MOD = 998244353;
static const int MAXN = 105;

ll Cbin[MAXN][MAXN];

ll modpow(ll a, ll e) {
    ll r = 1;
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

    // binomial coefficients
    for (int n = 0; n < MAXN; n++) {
        Cbin[n][0] = Cbin[n][n] = 1;
        for (int r = 1; r < n; r++) {
            Cbin[n][r] =
                (Cbin[n - 1][r - 1] + Cbin[n - 1][r]) % MOD;
        }
    }

    int T;
    cin >> T;

    while (T--) {
        int N;
        ll C;
        cin >> N >> C;

        vector<ll> A(N + 1);
        for (int i = 1; i <= N; i++) {
            cin >> A[i];
        }

        sort(A.begin() + 1, A.end());

        /*
            ge[k] = number of budget assignments
                    that result in AT LEAST k sales.
        */
        vector<ll> ge(N + 2, 0);

        // At least 0 sales: every budget assignment works.
        ge[0] = modpow(C, N);

        /*
            Fix k.

            Hall condition:
              for every i = 1..k,
              #customers with budget >= A[i] >= k+1-i.
        */
        for (int k = 1; k <= N; k++) {

            /*
                dp[j]:

                After processing all budget values from the current
                threshold upward, exactly j customers have had their
                budgets assigned into those processed intervals.

                All Hall conditions seen so far are satisfied.
            */
            vector<ll> dp(N + 1, 0);
            dp[0] = 1;

            /*
                Process:

                    [A[k], C]
                    [A[k-1], A[k)-1]
                    ...
                    [A[1], A[2)-1]

                from expensive to cheap.
            */
            for (int i = k; i >= 1; i--) {

                ll high;

                if (i == k) {
                    high = C + 1;
                } else {
                    high = A[i + 1];
                }

                ll width = high - A[i];

                /*
                    For i == k:
                        width = C+1-A[k]
                              = C-A[k]+1

                    Otherwise:
                        width = A[i+1]-A[i]
                */

                vector<ll> pw(N + 1, 1);
                for (int t = 1; t <= N; t++) {
                    pw[t] = pw[t - 1] * (width % MOD) % MOD;
                }

                vector<ll> ndp(N + 1, 0);

                for (int j = 0; j <= N; j++) {
                    if (dp[j] == 0) continue;

                    /*
                        There are N-j customers not assigned yet.

                        Choose t of them to have their budget
                        inside the current interval.
                    */
                    for (int t = 0; j + t <= N; t++) {

                        int nj = j + t;

                        /*
                            After processing down to A[i],
                            nj = #customers with budget >= A[i].

                            Hall requires:
                                nj >= k+1-i
                        */
                        if (nj < k + 1 - i)
                            continue;

                        ll ways = Cbin[N - j][t];
                        ways = ways * pw[t] % MOD;

                        ndp[nj] += dp[j] * ways % MOD;

                        if (ndp[nj] >= MOD)
                            ndp[nj] -= MOD;
                    }
                }

                dp.swap(ndp);
            }

            /*
                Now j customers have budget >= A[1].

                The remaining N-j customers must have budget
                in [1, A[1)-1].

                Each has A[1]-1 possibilities.
            */
            ll lowWidth = A[1] - 1;

            vector<ll> lowPow(N + 1, 1);

            for (int t = 1; t <= N; t++) {
                lowPow[t] =
                    lowPow[t - 1] * (lowWidth % MOD) % MOD;
            }

            ll waysAtLeastK = 0;

            for (int j = 0; j <= N; j++) {
                int remaining = N - j;

                waysAtLeastK +=
                    dp[j] * lowPow[remaining] % MOD;

                waysAtLeastK %= MOD;
            }

            ge[k] = waysAtLeastK;
        }

        ge[N + 1] = 0;

        /*
            exactly k =
                at least k
                -
                at least k+1
        */

        // wwr
        ll invTotal = modpow(modpow(C, N), MOD - 2);

        for (int k = 0; k <= N; k++) {
            ll exact =
                (ge[k] - ge[k + 1] + MOD) % MOD;

            exact = exact * invTotal % MOD;

            if (k) cout << ' ';
            cout << exact;
        }

        cout << '\n';
    }
    return 0;
}

// wewe w r