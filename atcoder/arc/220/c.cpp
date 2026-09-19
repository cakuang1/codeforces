#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N;
        int64 M, K;
        cin >> N >> M >> K;

        vector<int64> A(N);
        for (auto &x : A) cin >> x;

        vector<int64> ans(N, 0);

        // f = number of currently active interval-increments
        // extending from previous positions into current position.
        int64 f = 0;

        // Cheapest previous choices where we can switch
        // from "reduce" to "increase".
        priority_queue<
            int64,
            vector<int64>,
            greater<int64>
        > pq;

        for (int i = 0; i < N; i++) {
            int64 a = A[i];

            // If all f currently active intervals are extended to i,
            // current value becomes d.
            int64 d = (a + f) % M;

            // Greedily try the free option:
            // end d intervals before/at this boundary,
            // making current value 0.
            f -= d;

            // Alternative at this point:
            // instead of reducing by d,
            // increase by M-d.
            //
            // Switching to that alternative later changes f by +M
            // and costs M-d new interval starts.
            pq.push(M - d);

            if (f < 0) {
                // We need to retroactively choose one "increase"
                // alternative. Cheapest one is optimal.
                int64 cost = pq.top();

                if (cost <= K) {
                    K -= cost;
                    pq.pop();

                    // Switching one previous decision from
                    // -d to +(M-d) changes active count by exactly M.
                    f += M;
                } else {
                    // Cannot make A[i] become 0.
                    //
                    // So lexicographically best is to leave it A[i].
                    ans[i] = a;

                    // No old interval needs to cross this position.
                    // Start a fresh segment after i.
                    f = 0;

                    priority_queue<
                        int64,
                        vector<int64>,
                        greater<int64>
                    > empty;
                    swap(pq, empty);
                }
            }

            // Otherwise ans[i] stays 0.
        }

        for (int i = 0; i < N; i++) {
            if (i) cout << ' ';
            cout << ans[i];
        }
        cout << '\n';
    }

    return 0;
}