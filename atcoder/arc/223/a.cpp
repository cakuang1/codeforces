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
        int64 W;
        cin >> N >> W;

        vector<int64> w(N + 1), v(N + 1);
        vector<int64> prefix(N + 1, 0);

        for (int i = 1; i <= N; ++i) {
            cin >> w[i] >> v[i];
            prefix[i] = prefix[i - 1] + v[i];
        }

        int64 R = W;
        int64 chosenValue = 0;
        int64 answer = 0;

        for (int i = N; i >= 1; --i) {
            if (w[i] > R) {
                // Item i is impossible to take.
                continue;
            }

            // Skip i, then take every smaller item.
            answer = max(answer, chosenValue + prefix[i - 1]);

            // Take i and continue deciding smaller items.
            chosenValue += v[i];
            R -= w[i];
        }

        // Take every item selected along the continuing branch.
        answer = max(answer, chosenValue);

        cout << answer << '\n';
    }
}

// wrhoerhwirew l rs fsbyw fwkf sn wfic wf wer

// wewee wersd hweior

// we wrwbew w rs ewr sd ers esrs elri n. wer
// thsi wrkar sk wer
//  werwho dosuwerl