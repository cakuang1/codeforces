#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int H, W;
    cin >> H >> W;

    vector<string> S(H);
    for (int i = 0; i < H; i++) cin >> S[i];

    long long ans = 0;

    for (int h1 = 0; h1 < H; h1++) {
        for (int h2 = h1; h2 < H; h2++) {
            for (int w1 = 0; w1 < W; w1++) {
                for (int w2 = w1; w2 < W; w2++) {

                    bool ok = true;

                    for (int i = h1; i <= h2; i++) {
                        for (int j = w1; j <= w2; j++) {
                            int ri = h1 + h2 - i;
                            int rj = w1 + w2 - j;

                            if (S[i][j] != S[ri][rj]) {
                                ok = false;
                            }
                        }
                    }

                    if (ok) ans++;
                }
            }
        }
    }

    cout << ans << '\n';
}