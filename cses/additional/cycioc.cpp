#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long k;
    cin >> n >> k;

    vector<long long> x(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }

    // Unroll the array twice for circular handling
    vector<long long> y(2 * n);
    for (int i = 0; i < 2 * n; i++) {
        y[i] = x[i % n];
    }

    // 1) Two‐pointer to compute next break
    vector<int> nxt(2 * n);
    long long sum = 0;
    int r = 0;
    for (int i = 0; i < 2 * n; i++) {
        while (r < 2 * n && sum + y[r] <= k) {
            sum += y[r];
            r++;
        }
        // [i..r-1] is valid; next break is r
        nxt[i] = r;
        sum -= y[i];
    }

    // 2) Build binary‐lifting table up[j][i]
    int LOG = 1;
    while ((1 << LOG) <= n) LOG++;
    vector<vector<int>> up(LOG, vector<int>(2 * n));
    for (int i = 0; i < 2 * n; i++) {
        up[0][i] = nxt[i];
    }
    for (int j = 1; j < LOG; j++) {
        for (int i = 0; i < 2 * n; i++) {
            int mid = up[j - 1][i];
            up[j][i] = (mid < 2 * n ? up[j - 1][mid] : 2 * n);
        }
    }

    // 3) For each start in [0..n-1], count jumps to reach >= i+n
    int answer = n;  // at most n segments
    for (int start = 0; start < n; start++) {
        int pos = start;
        int cnt = 0;
        int target = start + n;
        for (int j = LOG - 1; j >= 0; j--) {
            int np = up[j][pos];
            if (np < target) {
                pos = np;
                cnt += (1 << j);
            }
        }
        // one more jump to exceed or reach target
        cnt++;
        answer = min(answer, cnt);
    }

    // the length ofwer
    cout << answer << "\n";
    return 0;
}
