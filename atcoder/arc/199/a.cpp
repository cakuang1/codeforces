#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;

        vector<string> A(N);
        for (auto &s : A) cin >> s;

        vector<int> R(N), C(N);
        for (int &x : R) cin >> x;
        for (int &x : C) cin >> x;

        string X(N, '0');
        string Y(N, '0');

        auto flipRow = [&](int i) {
            X[i] ^= 1;
            for (int j = 0; j < N; j++) {
                A[i][j] ^= 1;
            }
        };

        auto flipCol = [&](int j) {
            Y[j] ^= 1;
            for (int i = 0; i < N; i++) {
                A[i][j] ^= 1;
            }
        };

        // 1. Make the first row all 0.
        for (int j = 0; j < N; j++) {
            if (A[0][j] == '1') {
                flipCol(j);
            }
        }

        // 2. Any row with at least half 1s must be flipped.
        for (int i = 0; i < N; i++) {
            int cnt = 0;
            for (int j = 0; j < N; j++) {
                cnt += (A[i][j] == '1');
            }

            if (cnt >= (N + 1) / 2) {
                flipRow(i);
            }
        }

        // 3. Any column with at least half 1s must be flipped.
        for (int j = 0; j < N; j++) {
            int cnt = 0;
            for (int i = 0; i < N; i++) {
                cnt += (A[i][j] == '1');
            }

            if (cnt >= (N + 1) / 2) {
                flipCol(j);
            }
        }

        // 4. Check if we actually reached all desired sums.
        bool ok = true;

        for (int i = 0; i < N; i++) {
            int cnt = 0;
            for (int j = 0; j < N; j++) {
                cnt += (A[i][j] == '1');
            }

            if (cnt != R[i]) {
                ok = false;
            }
        }

        for (int j = 0; j < N; j++) {
            int cnt = 0;
            for (int i = 0; i < N; i++) {
                cnt += (A[i][j] == '1');
            }

            if (cnt != C[j]) {
                ok = false;
            }
        }

        if (!ok) {
            cout << "No\n";
        } else {
            cout << "Yes\n";
            cout << X << '\n';
            cout << Y << '\n';
        }
    }

    return 0;
}



// wewsdo wehr