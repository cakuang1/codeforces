#include <bits/stdc++.h>
using namespace std;

static const int MOD = 998244353;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<int> B(N);
    for (int &x : B) cin >> x;

    // prefUnknown[i] = # of -1 among B[0..i-1]
    // prefMin[i]     = minimum fixed value among B[0..i-1]
    vector<int> prefUnknown(N + 1, 0);
    vector<int> prefMin(N + 1, M + 1);

    for (int i = 0; i < N; ++i) {
        prefUnknown[i + 1] = prefUnknown[i];
        prefMin[i + 1] = prefMin[i];

        if (B[i] == -1) {
            prefUnknown[i + 1]++;
        } else {
            prefMin[i + 1] = min(prefMin[i + 1], B[i]);
        }
    }

    // sufUnknown[i] = # of -1 among B[i..N-1]
    // sufMax[i]     = maximum fixed value among B[i..N-1]
    vector<int> sufUnknown(N + 1, 0);
    vector<int> sufMax(N + 1, 0);

    for (int i = N - 1; i >= 0; --i) {
        sufUnknown[i] = sufUnknown[i + 1];
        sufMax[i] = sufMax[i + 1];

        if (B[i] == -1) {
            sufUnknown[i]++;
        } else {
            sufMax[i] = max(sufMax[i], B[i]);
        }
    }

    // pw[b][e] = b^e mod MOD.
    vector<vector<int>> pw(M + 1, vector<int>(N + 1, 1));

    for (int b = 0; b <= M; ++b) {
        for (int e = 1; e <= N; ++e) {
            pw[b][e] = (long long)pw[b][e - 1] * b % MOD;
        }
    }

    int totalUnknown = prefUnknown[N];

    // Every completion has at least one connected component.
    long long ans = pw[M][totalUnknown];

    // Cut after positions [0..cut-1].
    // Left  = [0..cut-1]
    // Right = [cut..N-1]
    for (int cut = 1; cut < N; ++cut) {
        int leftUnknown = prefUnknown[cut];
        int rightUnknown = sufUnknown[cut];

        int leftFixedMin = prefMin[cut];
        int rightFixedMax = sufMax[cut];

        // Let x = minimum value on the left.
        for (int x = 1; x <= M; ++x) {

            // L(x) = ways that every left value >= x.
            long long Lx = 0;

            if (leftFixedMin >= x) {
                Lx = pw[M - x + 1][leftUnknown];
            }

            // L(x+1) = ways that every left value >= x+1.
            long long Lnext = 0;

            if (x < M && leftFixedMin >= x + 1) {
                Lnext = pw[M - x][leftUnknown];
            }

            // Therefore:
            // exactLeftMin = ways that min(left) = x.
            long long exactLeftMin = (Lx - Lnext + MOD) % MOD;

            // Right side needs every value < x.
            long long rightWays = 0;

            if (rightFixedMax < x) {
                rightWays = pw[x - 1][rightUnknown];
            }

            ans += exactLeftMin * rightWays % MOD;
            ans %= MOD;
        }
    }

    cout << ans % MOD << '\n';
    return 0;
}