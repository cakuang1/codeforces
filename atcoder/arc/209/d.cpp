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

        vector<int> A(N + 1);
        int unknown = 0;

        for (int i = 1; i <= N; ++i) {
            cin >> A[i];
            if (A[i] == -1) ++unknown;
        }

        // ------------------------------------------------------------
        // Case 0: no -1
        // Nothing to choose.
        // ------------------------------------------------------------

        // ------------------------------------------------------------
        // Case 1: exactly one -1
        // ------------------------------------------------------------
        if (unknown == 1) {
            int pos = -1;
            for (int i = 1; i <= N; ++i) {
                if (A[i] == -1) {
                    pos = i;
                    break;
                }
            }

            /*
                If some earlier position points to pos:

                    i < pos, A[i] = pos

                then B[i] = A[pos].

                This occurs BEFORE B[pos], so we must minimize it:
                set A[pos] = 1.
            */
            bool pointed_from_left = false;

            for (int i = 1; i < pos; ++i) {
                if (A[i] == pos) {
                    pointed_from_left = true;
                    break;
                }
            }

            if (pointed_from_left) {
                A[pos] = 1;
            } else {
                /*
                    Now the first place affected by A[pos] is B[pos].

                    If we choose A[pos] = j, then

                        B[pos] = A[j].

                    So choose j with minimum A[j].

                    We can also choose j = pos, in which case
                        A[pos] = pos
                        B[pos] = pos.

                    If B[pos] ties, choose smaller j because later
                    positions pointing to pos will have B = A[pos] = j.
                */

                int bestValue = pos; // choice j = pos
                int bestIndex = pos;

                for (int j = 1; j <= N; ++j) {
                    if (j == pos) continue;

                    if (A[j] < bestValue ||
                        (A[j] == bestValue && j < bestIndex)) {
                        bestValue = A[j];
                        bestIndex = j;
                    }
                }

                A[pos] = bestIndex;
            }
        }

        // ------------------------------------------------------------
        // Case 2: at least two -1s
        // ------------------------------------------------------------
        else if (unknown >= 2) {

            /*
                Easy special case.

                If A[1] is unknown:
                    set A[1] = 1.

                Then every other unknown can also be 1.

                Similarly if A[1] is already 1.
            */
            if (A[1] == -1 || A[1] == 1) {
                for (int i = 1; i <= N; ++i) {
                    if (A[i] == -1)
                        A[i] = 1;
                }
            }
            else {
                /*
                    First greedy step.

                    Suppose i < A[i] and A[A[i]] is unknown.

                    Then B[i] = A[A[i]].

                    Since i occurs before that unknown position itself,
                    lexicographically we absolutely want

                        B[i] = 1.

                    Therefore set A[A[i]] = 1.
                */
                for (int i = 1; i <= N; ++i) {
                    if (A[i] != -1 &&
                        A[i] > i &&
                        A[A[i]] == -1) {
                        A[A[i]] = 1;
                    }
                }

                /*
                    p = position whose value will be 1.
                    Every remaining -1 will usually become p.

                    First candidate:
                      - first existing position containing 1;
                      - if none exists, use the LAST remaining -1.

                    Why last?
                    If

                        A[x] = p

                    then B[x] = A[p] = 1.

                    We want to sacrifice the latest possible unknown
                    position by making A[p] = 1.
                */
                int p = -1;

                for (int i = 1; i <= N; ++i) {
                    if (A[i] == 1) {
                        p = i;
                        break;
                    }

                    if (A[i] == -1) {
                        // If no 1 ever appears, this eventually becomes
                        // the last unknown.
                        p = i;
                    }
                }

                /*
                    Now handle a different conflict.

                    Suppose

                        A[i] = x < i
                        A[x] = -1.

                    Position x occurred earlier.
                    Normally we wanted A[x] = p so B[x] = 1.

                    But now:

                        B[i] = A[x] = p.

                    Therefore at B[i], the numerical size of p matters.

                    We should choose the earliest unknown position AFTER i
                    to become the special A[p] = 1.

                    Only the FIRST such i matters because lexicographic
                    order prioritizes it.
                */
                for (int i = 1; i <= N; ++i) {
                    if (A[i] != -1 &&
                        A[i] < i &&
                        A[A[i]] == -1) {

                        int q = i + 1;

                        while (q <= N && A[q] != -1)
                            ++q;

                        if (q <= N)
                            p = min(p, q);

                        break;
                    }
                }

                /*
                    Every remaining unknown points to p:

                        A[i] = p
                    =>  B[i] = A[p] = 1.

                    And p itself contains 1.
                */
                for (int i = 1; i <= N; ++i) {
                    if (A[i] == -1)
                        A[i] = p;
                }

                A[p] = 1;
            }
        }

        // Construct B[i] = A[A[i]]
        for (int i = 1; i <= N; ++i) {
            if (i > 1) cout << ' ';
            cout << A[A[i]];
        }
        cout << '\n';
    }

    return 0;
}

// wecosntsudfw rhsdi wrsusof weler
// wrhsoi hworh