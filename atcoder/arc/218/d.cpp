#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;

    vector<int> P(N + 1);
    for (int i = 1; i <= N; i++) cin >> P[i];

    // ------------------------------------------------------------
    // 1. Split P into maximal strictly decreasing blocks.
    //
    // Example:
    // P = [2,1,4,6,3,5]
    //
    // blocks:
    // [2,1] [4] [6,3] [5]
    // ------------------------------------------------------------

    vector<int> block(N + 1);
    vector<int> L, R;

    int i = 1;

    while (i <= N) {
        int l = i;

        while (i < N && P[i] > P[i + 1]) {
            i++;
        }

        int r = i;

        int id = (int)L.size();
        L.push_back(l);
        R.push_back(r);

        for (int p = l; p <= r; p++) {
            block[p] = id;
        }

        i++;
    }

    int B = L.size();

    // ------------------------------------------------------------
    // 2. nextPos[p]
    //
    // Suppose p lies in block D_x and y = P[p].
    //
    // If y > max(D_{x+1}):
    //      next chosen element = min(D_x)
    //
    // Otherwise:
    //      next chosen element =
    //      smallest value in D_{x+1} which is >= y
    //
    // Since each block is decreasing by value,
    // "smallest value >= y" is the RIGHTMOST position
    // in the next block having value >= y.
    // ------------------------------------------------------------

    vector<int> nextPos(N + 1);

    for (int b = 0; b < B; b++) {
        int l = L[b];
        int r = R[b];

        // No transition needed from the final block.
        if (b == B - 1) {
            for (int p = l; p <= r; p++) {
                nextPos[p] = p;
            }
            continue;
        }

        int nl = L[b + 1];
        int nr = R[b + 1];

        // Maximum of next decreasing block is its first element.
        int maxNext = P[nl];

        for (int p = l; p <= r; p++) {
            int y = P[p];

            if (y > maxNext) {
                // Can't enter next block yet.
                // Lower ourselves as much as possible in current block.
                nextPos[p] = r;
            }
            else {
                // Find rightmost q in next block with P[q] >= y.
                //
                // P[nl..nr] is strictly decreasing.
                int lo = nl, hi = nr;
                int ans = nl;

                while (lo <= hi) {
                    int mid = (lo + hi) / 2;

                    if (P[mid] >= y) {
                        ans = mid;
                        lo = mid + 1;
                    }
                    else {
                        hi = mid - 1;
                    }
                }

                nextPos[p] = ans;
            }
        }
    }

    // ------------------------------------------------------------
    // 3. Binary lifting.
    //
    // up[k][v] = position reached after 2^k greedy jumps.
    //
    // One jump = choosing one more subsequence element.
    // It can:
    //      stay in the same block
    // or
    //      move into the next block.
    // ------------------------------------------------------------

    int LOG = 1;
    while ((1 << LOG) <= N) LOG++;

    vector<vector<int>> up(LOG, vector<int>(N + 1));

    for (int v = 1; v <= N; v++) {
        up[0][v] = nextPos[v];
    }

    for (int k = 1; k < LOG; k++) {
        for (int v = 1; v <= N; v++) {
            up[k][v] = up[k - 1][up[k - 1][v]];
        }
    }

    // ------------------------------------------------------------
    // 4. Queries.
    //
    // If l,r are in same decreasing block:
    //      max score = 0
    //      one element is enough.
    //
    // Otherwise:
    //      start from min(D_i) = rightmost element of first block.
    //
    //      Binary lift as far as possible while still landing
    //      BEFORE the target block.
    //
    //      Then take one final greedy jump into target block.
    // ------------------------------------------------------------

    while (Q--) {
        int l, r;
        cin >> l >> r;

        int startBlock = block[l];
        int targetBlock = block[r];

        if (startBlock == targetBlock) {
            cout << 1 << '\n';
            continue;
        }

        // wewhsod weri
        // Start from minimum of first block.
        int cur = R[startBlock];

        // We have already selected cur.
        long long answer = 1;

        // Stay strictly before the target block.
        for (int k = LOG - 1; k >= 0; k--) {
            int to = up[k][cur];

            if (block[to] < targetBlock) {
                cur = to;
                answer += (1LL << k);
            }
        }

        // One final jump reaches target block.
        cur = nextPos[cur];
        answer++;

        cout << answer << '\n';
    }

    return 0;
}