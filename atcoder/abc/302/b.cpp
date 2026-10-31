#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int h, w;
    cin >> h >> w;

    vector<string> s(h);
    for (auto &x : s) cin >> x;

    string target = "snuke";

    // All 8 directions
    int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            for (int d = 0; d < 8; d++) {
                bool ok = true;

                for (int k = 0; k < 5; k++) {
                    int x = i + k * dx[d];
                    int y = j + k * dy[d];

                    if (x < 0 || x >= h || y < 0 || y >= w) {
                        ok = false;
                        break;
                    }

                    if (s[x][y] != target[k]) {
                        ok = false;
                        break;
                    }
                }

                if (ok) {
                    for (int k = 0; k < 5; k++) {
                        int x = i + k * dx[d];
                        int y = j + k * dy[d];

                        cout << x + 1 << " " << y + 1 << '\n';
                    }
                    return 0;
                }
            }
        }
    }

    return 0;
}