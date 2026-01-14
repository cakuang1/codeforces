#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<vector<int>> a(N, vector<int>(N, 0));

    int r = 0;
    int c = (N - 1) / 2;
    a[r][c] = 1;

    for (int k = 1; k < N * N; k++) {
        int nr = (r - 1 + N) % N;
        int nc = (c + 1) % N;

        if (a[nr][nc] == 0) {
            r = nr;
            c = nc;
        } else {
            r = (r + 1) % N;
            // c stays the same
        }
        a[r][c] = k + 1;
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (j) cout << ' ';
            cout << a[i][j];
        }
        cout << '\n';
    }
    return 0;
}
