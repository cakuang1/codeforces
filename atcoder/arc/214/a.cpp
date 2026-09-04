#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<string> S(N);
    for (auto &row : S) cin >> row;

    // Anti-diagonal is determined by i + j.
    // With 0-indexing, sums go from 0 to 2N-2.
    for (int d = 0; d <= 2 * N - 2; d++) {
        char value = '?';

        // First, determine what digit this anti-diagonal must have.
        for (int i = 0; i < N; i++) {
            int j = d - i;

            if (j < 0 || j >= N) continue;

            if (S[i][j] != '?') {
                if (value == '?') {
                    value = S[i][j];
                } else if (value != S[i][j]) {
                    cout << -1 << '\n';
                    return 0;
                }
            }
        }

        // If no fixed digit exists, choose 0.
        if (value == '?') value = '0';

        // Fill all ? on this anti-diagonal.
        for (int i = 0; i < N; i++) {
            int j = d - i;

            if (j < 0 || j >= N) continue;

            if (S[i][j] == '?') {
                S[i][j] = value;
            }
        }
    }

    for (auto &row : S) {
        cout << row << '\n';
    }

    return 0;
}