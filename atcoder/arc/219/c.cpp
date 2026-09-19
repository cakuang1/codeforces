#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int64 H, W;
    cin >> H >> W;

    int N;
    cin >> N;

    // row -> list of door columns
    map<int64, vector<int64>> rows;

    for (int i = 0; i < N; i++) {
        int64 a, b;
        cin >> a >> b;
        rows[a].push_back(b);
    }

    // ------------------------------------------------------------
    // Case 1:
    // Never use the elevator at column W.
    //
    // For each row, go from col 1 to its rightmost door and back.
    // ------------------------------------------------------------
    int64 leftOnly = 0;

    // ------------------------------------------------------------
    // Case 2:
    // Use both elevators.
    //
    // base = sum of all non-crossing costs a_i.
    //
    // Replacing row i by a crossing changes its cost by
    //
    // delta_i = (W - 1) - a_i.
    //
    // Need a positive even number of crossings.
    // ------------------------------------------------------------
    int64 base = 0;
    vector<int64> delta;

    for (auto &[row, cols] : rows) {
        sort(cols.begin(), cols.end());

        // ---- left-only cost ----
        int64 rightmost = cols.back();
        leftOnly += 2 * (rightmost - 1);

        // ---- compute largest gap for non-crossing solution ----
        //
        // Include sentinels 1 and W.
        //
        // [1, door1, door2, ..., door_m, W]
        //
        int64 maxGap = 0;

        int64 prev = 1;

        for (int64 b : cols) {
            maxGap = max(maxGap, b - prev);
            prev = b;
        }

        maxGap = max(maxGap, W - prev);

        // Cheapest type-3 / non-crossing cost
        int64 a_i = 2 * (W - 1) - 2 * maxGap;

        base += a_i;

        // Cost difference if this row becomes a full crossing
        int64 d = (W - 1) - a_i;
        delta.push_back(d);
    }

    // If we use column W, we need at least 2 crossing rows.
    const int64 INF = (1LL << 62);
    int64 crossAnswer = INF;

    if ((int)delta.size() >= 2) {
        sort(delta.begin(), delta.end());

        int64 pref = 0;

        for (int k = 1; k <= (int)delta.size(); k++) {
            pref += delta[k - 1];

            // Positive even number of crossing rows: 2,4,6,...
            if (k % 2 == 0) {
                crossAnswer = min(crossAnswer, base + pref);
            }
        }
    }

    int64 answer = min(leftOnly, crossAnswer);

    cout << answer << '\n';

    return 0;
}


// erwingni ad slosgin ssta wer
