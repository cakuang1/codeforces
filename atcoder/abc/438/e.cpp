#include <bits/stdc++.h>
using namespace std;

using int64 = long long;
using i128 = __int128_t;

static string to_string_i128(i128 x) {
    if (x == 0) return "0";
    bool neg = false;
    if (x < 0) { neg = true; x = -x; }
    string s;
    while (x > 0) {
        int d = (int)(x % 10);
        s.push_back(char('0' + d));
        x /= 10;
    }
    if (neg) s.push_back('-');
    reverse(s.begin(), s.end());
    return s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;
    vector<int> A(N + 1);
    for (int i = 1; i <= N; i++) cin >> A[i];

    // We need up to 2^k >= 1e9
    const int LOG = 31; // 2^30 ~ 1.07e9

    vector<vector<int>> up(LOG, vector<int>(N + 1));
    vector<vector<i128>> sum(LOG, vector<i128>(N + 1));

    // Base: 1 step from v -> A[v], and we add v water in that step.
    for (int v = 1; v <= N; v++) {
        up[0][v] = A[v];
        sum[0][v] = (i128)v;
    }

    // Build doubling tables
    for (int k = 1; k < LOG; k++) {
        for (int v = 1; v <= N; v++) {
            int mid = up[k - 1][v];
            up[k][v] = up[k - 1][mid];
            sum[k][v] = sum[k - 1][v] + sum[k - 1][mid];
        }
    }

    // Each query: amount in bucket B immediately after T-th operation.
    // A bucket starting at B visits holders: B, A[B], A[A[B]], ... (T steps)
    // Water added is sum of the first T holders => use lifting with sums.
    for (int qi = 0; qi < Q; qi++) {
        long long T;
        int B;
        cin >> T >> B;

        i128 ans = 0;
        int cur = B;
        long long t = T;

        for (int k = 0; k < LOG; k++) {
            if (t & (1LL << k)) {
                ans += sum[k][cur];
                cur = up[k][cur];
            }
        }

        cout << to_string_i128(ans) << "\n";
    }

    return 0;
}

// w sdf wrsd sdf scontains tsth sif wer
// find wtwhsd fwetconnectesd pscomoesnt sthis wer si wtint ? wrroot werit we> werthwern wew
// 