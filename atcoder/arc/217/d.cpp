#include <bits/stdc++.h>
using namespace std;

using int64 = long long;
using u64 = unsigned long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N, M;
        cin >> N >> M;

        vector<int> A(N + 1);
        for (int i = 1; i <= N; i++) {
            cin >> A[i];
        }

        // C[i] = largest money state needed at layer i.
        vector<int> C(N + 2);
        C[1] = M;

        for (int i = 1; i <= N; i++) {
            C[i + 1] = min(
                C[i],
                max(A[i] - 1, C[i] - A[i])
            );
        }

        /*
            dq[j] + lazy = d[current_layer][j]

            Start with D[N+1]:
            d[N+1][c] = 0 for all needed c.
        */
        deque<int64> dq(C[N + 1] + 1, 0);
        int64 lazy = 0;

        // Recover D[i] from D[i+1], backwards.
        for (int i = N; i >= 1; i--) {
            int a = A[i];
            int ci = C[i];

            // If a > ci, then none of the relevant money states
            // can afford this item.
            //
            // d[i][c] = d[i+1][c]
            if (a > ci) {
                continue;
            }

            /*
                D[i] =

                [ d'[0], ..., d'[a-1] ]

                followed by

                [ a+d'[0], ..., a+d'[ci-a] ]

                where d'[x] = d[i+1][x].

                left length  = a
                right length = ci-a+1
            */

            int leftLen = a;
            int rightLen = ci - a + 1;

            if (leftLen > rightLen) {
                /*
                    D[i+1] is the longer LEFT source prefix.

                    Existing actual deque represents:

                    [d'[0], ..., d'[a-1]]

                    Need to append:

                    [a+d'[0], ..., a+d'[rightLen-1]]

                    Since stored value = actual - lazy,
                    if dq[j] stores d'[j]-lazy,
                    then a+d'[j]-lazy = dq[j]+a.
                */

                vector<int64> add;
                add.reserve(rightLen);

                for (int j = 0; j < rightLen; j++) {
                    add.push_back(dq[j] + a);
                }

                for (int64 x : add) {
                    dq.push_back(x);
                }

            } else {
                /*
                    D[i+1] is the longer RIGHT source prefix.

                    We want:

                    [d'[0], ..., d'[a-1],
                     a+d'[0], ..., a+d'[rightLen-1]]

                    Rewrite as:

                    a + [
                        d'[0]-a, ..., d'[a-1]-a,
                        d'[0], ..., d'[rightLen-1]
                    ]

                    So:
                    1. prepend the adjusted left block
                    2. lazy += a
                */

                vector<int64> add;
                add.reserve(leftLen);

                for (int j = 0; j < leftLen; j++) {
                    // dq[j] stores d'[j] - lazy.
                    // We need stored version of d'[j] - a
                    // before increasing lazy.
                    add.push_back(dq[j] - a);
                }

                // Preserve original order when pushing to front.
                for (int j = leftLen - 1; j >= 0; j--) {
                    dq.push_front(add[j]);
                }

                lazy += a;
            }
        }

        /*
            Now:
            dq[k] + lazy = d[1][k] = f(k)

            Need XOR of k * f(k), k = 1..M.
        */
        u64 ans = 0;

        for (int k = 1; k <= M; k++) {
            int64 f = dq[k] + lazy;

            u64 value = (u64)k * (u64)f;
            ans ^= value;
        }

        cout << ans << '\n';
    }

    return 0;
}
