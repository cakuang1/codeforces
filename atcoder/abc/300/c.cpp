#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int h, w;
    cin >> h >> w;

    vector<string> g(h);
    for (auto &s : g) cin >> s;

    int n = min(h, w);
    vector<int> ans(n + 1, 0);

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (g[i][j] != '#') continue;

            int sz = 0;

            for (int d = 1; ; d++) {
                if (i - d < 0 || i + d >= h ||
                    j - d < 0 || j + d >= w)
                    break;

                if (g[i-d][j-d] != '#' ||
                    g[i-d][j+d] != '#' ||
                    g[i+d][j-d] != '#' ||
                    g[i+d][j+d] != '#')
                    break;

                sz++;
            }

            if (sz > 0) ans[sz]++;
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << ans[i] << (i == n ? '\n' : ' ');
    }

    return 0;
}