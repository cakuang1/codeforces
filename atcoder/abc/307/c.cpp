
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int ha, wa, hb, wb, hx, wx;
    cin >> ha >> wa;
    vector<string> a(ha);
    for (auto &s : a) cin >> s;

    cin >> hb >> wb;
    vector<string> b(hb);
    for (auto &s : b) cin >> s;

    cin >> hx >> wx;
    vector<string> x(hx);
    for (auto &s : x) cin >> s;

    vector<pair<int, int>> A, B;

    for (int i = 0; i < ha; i++) {
        for (int j = 0; j < wa; j++) {
            if (a[i][j] == '#') A.push_back({i, j});
        }
    }

    for (int i = 0; i < hb; i++) {
        for (int j = 0; j < wb; j++) {
            if (b[i][j] == '#') B.push_back({i, j});
        }
    }

    // Try every translation of A and B.
    for (int ai = -10; ai <= 10; ai++) {
        for (int aj = -10; aj <= 10; aj++) {
            for (int bi = -10; bi <= 10; bi++) {
                for (int bj = -10; bj <= 10; bj++) {

                    vector<string> cur(hx, string(wx, '.'));
                    bool ok = true;

                    for (auto [i, j] : A) {
                        int r = i + ai;
                        int c = j + aj;

                        if (r < 0 || r >= hx || c < 0 || c >= wx) {
                            ok = false;
                            break;
                        }

                        cur[r][c] = '#';
                    }

                    if (!ok) continue;

                    for (auto [i, j] : B) {
                        int r = i + bi;
                        int c = j + bj;

                        if (r < 0 || r >= hx || c < 0 || c >= wx) {
                            ok = false;
                            break;
                        }

                        cur[r][c] = '#';
                    }

                    if (ok && cur == x) {
                        cout << "Yes\n";
                        return 0;
                    }
                }
            }
        }
    }

    cout << "No\n";
    return 0;
}
