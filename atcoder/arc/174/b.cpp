#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        vector<int64> A(5), P(5);

        for (int i = 0; i < 5; ++i) {
            cin >> A[i];
        }

        for (int i = 0; i < 5; ++i) {
            cin >> P[i];
        }

        // Missing contribution needed to make the average at least 3.
        int64 deficit =
            2 * A[0] + A[1] - A[3] - 2 * A[4];

        if (deficit <= 0) {
            cout << 0 << '\n';
            continue;
        }

        int64 cost4 = P[3];  // +1 contribution
        int64 cost5 = P[4];  // +2 contribution

        int64 answer = (deficit / 2) * min(2 * cost4, cost5);

        if (deficit % 2 == 1) {
            answer += min(cost4, cost5);
        }

        cout << answer << '\n';
    }

    return 0;
}