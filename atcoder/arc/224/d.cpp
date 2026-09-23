#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

int digits(int x) {
    if (x < 10) return 1;
    if (x < 100) return 2;
    if (x < 1000) return 3;
    if (x < 10000) return 4;
    if (x < 100000) return 5;
    if (x < 1000000) return 6;
    return 7;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N, K;
        cin >> N >> K;

        // Since K <= 10^6, 2^20 is already enough for every possible K.
        bool possible;
        if (N >= 20) {
            possible = true;
        } else {
            possible = ((1LL << N) >= K);
        }

        if (!possible) {
            cout << -1 << '\n';
            continue;
        }

        int remaining = K;
        int x = K;              // Give cheap patterns to large numbers first.
        int pop = 0;
        int64 choose = 1;       // C(N, 0)
        int64 answer = 0;

        while (remaining > 0) {
            // There are C(N, pop) bit patterns having exactly pop set bits.
            int take = (int)min<int64>(remaining, choose);

            // Assign this popcount to x, x-1, ..., x-take+1.
            for (int i = 0; i < take; i++) {
                answer += 1LL * pop * digits(x);
                x--;
            }

            remaining -= take;
            if (remaining == 0) break;

            // Compute C(N, pop + 1) from C(N, pop):
            //
            // C(N, pop+1) = C(N, pop) * (N-pop) / (pop+1)
            //
            // We cap it at K: anything above K is already enough.
            choose = choose * (N - pop) / (pop + 1);
            choose = min<int64>(choose, K);

            pop++;
        }

        cout << answer << '\n';
    }
}