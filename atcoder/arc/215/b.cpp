#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;

        vector<int> A(2 * N);
        for (int &x : A) cin >> x;

        // parity[x] = parity of the segment containing
        // the first occurrence of x.
        // -1 means x has not appeared yet.
        vector<int> parity(N + 1, -1);

        // 0 = odd-numbered segment
        // 1 = even-numbered segment
        int cur = 0;

        vector<int> cuts;

        for (int i = 0; i < 2 * N; ++i) {
            int x = A[i];

            if (parity[x] == -1) {
                // First occurrence of x.
                parity[x] = cur;
            } else {
                // Second occurrence.
                // It must be in the opposite parity segment.
                if (parity[x] == cur) {
                    // Put divider immediately before A[i].
                    //
                    // A[i] is gem i+1 in 1-indexing,
                    // so the divider position is i.
                    cuts.push_back(i);

                    cur ^= 1;
                }
            }
        }

        cout << cuts.size() << '\n';

        for (int i = 0; i < (int)cuts.size(); ++i) {
            if (i) cout << ' ';
            cout << cuts[i];
        }
        cout << '\n';
    }

    return 0;
}

// waltes ssd wre


// w