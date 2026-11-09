
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<string> s(n);
    for (auto &row : s) cin >> row;

    vector<string> pattern = {
        "###.?????",
        "###.?????",
        "###.?????",
        "....?????",
        "?????????",
        "?????....",
        "?????.###",
        "?????.###",
        "?????.###"
    };

    for (int i = 0; i + 9 <= n; i++) {
        for (int j = 0; j + 9 <= m; j++) {

            bool ok = true;

            for (int x = 0; x < 9; x++) {
                for (int y = 0; y < 9; y++) {
                    if (pattern[x][y] != '?' &&
                        s[i + x][j + y] != pattern[x][y]) {
                        ok = false;
                    }
                }
            }

            if (ok) {
                cout << i + 1 << " " << j + 1 << '\n';
            }
        }
    }

    return 0;
}
