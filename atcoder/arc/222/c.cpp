#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = (1LL << 62);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;

        vector<vector<ll>> A(N, vector<ll>(N));

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cin >> A[i][j];
            }
        }

        /*
            cost[i][j]:

            Cost if (i,j) is chosen as the spine cell.

            We whiten the cells immediately to its
            left and right.

                 WHITE  SPINE  WHITE
        */
        vector<vector<ll>> cost(N, vector<ll>(N, 0));

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (j - 1 >= 0)
                    cost[i][j] += A[i][j - 1];

                if (j + 1 < N)
                    cost[i][j] += A[i][j + 1];
            }
        }

        /*
            up[i][j]:

            Minimum cost of a spine from row 0 to row i,
            where the spine is at column j on row i.

            Consecutive spine cells must differ by 1 column:

                    X
                   /
                  X

            or

                  X
                   \
                    X
        */
        vector<vector<ll>> up(N, vector<ll>(N, INF));

        for (int j = 0; j < N; j++)
            up[0][j] = cost[0][j];

        for (int i = 1; i < N; i++) {
            for (int j = 0; j < N; j++) {

                if (j - 1 >= 0) {
                    up[i][j] = min(
                        up[i][j],
                        up[i - 1][j - 1] + cost[i][j]
                    );
                }

                if (j + 1 < N) {
                    up[i][j] = min(
                        up[i][j],
                        up[i - 1][j + 1] + cost[i][j]
                    );
                }
            }
        }

        /*
            down[i][j]:

            Same thing, except going from row N-1 upward.
        */
        vector<vector<ll>> down(N, vector<ll>(N, INF));

        for (int j = 0; j < N; j++)
            down[N - 1][j] = cost[N - 1][j];

        for (int i = N - 2; i >= 0; i--) {
            for (int j = 0; j < N; j++) {

                if (j - 1 >= 0) {
                    down[i][j] = min(
                        down[i][j],
                        down[i + 1][j - 1] + cost[i][j]
                    );
                }

                if (j + 1 < N) {
                    down[i][j] = min(
                        down[i][j],
                        down[i + 1][j + 1] + cost[i][j]
                    );
                }
            }
        }

        /*
            whole[i][j]:

            Minimum cost of an entire top-to-bottom spine
            that passes through (i,j).

            up and down both counted cost[i][j],
            so subtract it once.
        */
        vector<vector<ll>> whole(N, vector<ll>(N));

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                whole[i][j] =
                    up[i][j] + down[i][j] - cost[i][j];
            }
        }

        /*
            Starting position = (i,j).

            It must be a WHITE cell next to the spine.

            Therefore the spine in this row can be:

                SPINE START

            at j-1,

            or

                START SPINE

            at j+1.

            Choose the cheaper one.
        */
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {

                ll ans = INF;

                if (j - 1 >= 0)
                    ans = min(ans, whole[i][j - 1]);

                if (j + 1 < N)
                    ans = min(ans, whole[i][j + 1]);

                cout << ans;

                if (j + 1 < N)
                    cout << ' ';
            }

            cout << '\n';
        }
    }
}