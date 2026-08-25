#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    const ll INF = (1LL << 60);

    while (T--) {
        int N;
        cin >> N;

        vector<int> A(N + 1);
        for (int i = 1; i <= N; i++) {
            cin >> A[i];
        }

        /*
            dp0[i]:
                minimum (# swaps + # boundaries between unequal values)
                after handling A[1..i],
                where A[i-1], A[i] are NOT swapped.

                The final value in the resulting prefix is A[i].

            dp1[i]:
                same thing, but A[i-1], A[i] ARE swapped.

                The ending looks like:

                    ..., A[i], A[i-1]

                so the final value is A[i-1].
        */

        vector<ll> dp0(N + 1, INF);
        vector<ll> dp1(N + 1, INF);

        // One element: no swaps, no boundaries yet.
        dp0[1] = 0;

        for (int i = 2; i <= N; i++) {

            // -------------------------------------------
            // Don't swap (i-1, i).
            // -------------------------------------------

            // Previous state was normal:
            // ... A[i-1], A[i]
            dp0[i] = min(
                dp0[i],
                dp0[i - 1] + (A[i - 1] != A[i])
            );

            // Previous state swapped (i-2, i-1):
            //
            // ... A[i-1], A[i-2], A[i]
            //
            // The previous LAST element is A[i-2].
            if (i >= 3) {
                dp0[i] = min(
                    dp0[i],
                    dp1[i - 1] + (A[i - 2] != A[i])
                );
            }

            // -------------------------------------------
            // Swap (i-1, i).
            //
            // They appear as:
            //
            //      A[i], A[i-1]
            //
            // Cost:
            //   +1 for the swap
            //   +(A[i] != A[i-1]) for internal boundary
            // -------------------------------------------

            if (i == 2) {
                // No prefix before this pair.
                dp1[i] =
                    1 + (A[i] != A[i - 1]);
            } else {

                // First i-2 elements ended normally.
                //
                // ... A[i-2] | A[i], A[i-1]
                dp1[i] = min(
                    dp1[i],
                    dp0[i - 2]
                    + 1
                    + (A[i - 2] != A[i])
                    + (A[i] != A[i - 1])
                );

                // First i-2 elements ended with a swap:
                //
                // ... A[i-3] | A[i], A[i-1]
                if (i >= 4) {
                    dp1[i] = min(
                        dp1[i],
                        dp1[i - 2]
                        + 1
                        + (A[i - 3] != A[i])
                        + (A[i] != A[i - 1])
                    );
                }
            }
        }

        /*
            DP counted:

                swaps + unequal adjacent boundaries

            If a final sequence has k unequal boundaries,
            it has k+1 runs, therefore needs k+1 erase operations.

            So add 1.
        */
        cout << min(dp0[N], dp1[N]) + 1 << '\n';
    }
}
// wwsd eurs e adses e 


// w ewr. we


// r sdmwitwh siewrl wer

// wewrhw yad this boole ns
/