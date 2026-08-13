#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> P(N), Q(N);
    for (int &x : P) {
        cin >> x;
        --x;
    }
    for (int &x : Q) {
        cin >> x;
        --x;
    }

    vector<string> A(N, string(N, '?'));

    for (int i = 0; i < N; ++i) {
        int r = P[i];
        int c = Q[N - 1 - i];

        // First: put 0 in all still-empty cells of row P[i].
        for (int j = 0; j < N; ++j) {
            if (A[r][j] == '?')
                A[r][j] = '0';
        }

        // Then: put 1 in all still-empty cells of column Q[N-1-i].
        for (int j = 0; j < N; ++j) {
            if (A[j][c] == '?')
                A[j][c] = '1';
        }
    }

    for (auto &row : A)
        cout << row << '\n';
}
// w    