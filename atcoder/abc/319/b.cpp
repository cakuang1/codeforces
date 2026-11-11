
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    int grid[100][100] = {};

    for (int i = 0; i < N; i++) {
        int A, B, C, D;
        cin >> A >> B >> C >> D;

        for (int x = A; x < B; x++) {
            for (int y = C; y < D; y++) {
                grid[x][y]++;
            }
        }
    }

    int ans = 0;

    for (int x = 0; x < 100; x++) {
        for (int y = 0; y < 100; y++) {
            if (grid[x][y] > 0) {
                ans++;
            }
        }
    }

    cout << ans << '\n';

    return 0;
}
