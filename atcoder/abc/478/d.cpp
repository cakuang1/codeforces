#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;

    vector<vector<pair<int, int>>> intervals(Q + 1);

    for (int i = 0; i < Q; ++i) {
        int L, R, X;
        cin >> L >> R >> X;
        intervals[X].push_back({L, R});
    }

    vector<int> diff(N + 2, 0);

    for (int x = 1; x <= Q; ++x) {
        auto &v = intervals[x];
        if (v.empty()) continue;

        sort(v.begin(), v.end());

        int l = v[0].first;
        int r = v[0].second;

        for (int i = 1; i < (int)v.size(); ++i) {
            auto [nextL, nextR] = v[i];

            if (nextL <= r + 1) {
                // Overlapping or adjacent intervals.
                r = max(r, nextR);
            } else {
                diff[l]++;
                diff[r + 1]--;

                l = nextL;
                r = nextR;
            }
        }

        // Add the final merged interval.
        diff[l]++;
        diff[r + 1]--;
    }

    int count = 0;
    for (int i = 1; i <= N; ++i) {
        count += diff[i];
        cout << count << (i == N ? '\n' : ' ');
    }

    return 0;
}



// w