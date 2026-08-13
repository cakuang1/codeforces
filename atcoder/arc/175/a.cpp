#include <bits/stdc++.h>
using namespace std;

static constexpr long long MOD = 998244353;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> P(N);
    vector<int> pos(N);

    for (int t = 0; t < N; ++t) {
        cin >> P[t];
        --P[t];
        pos[P[t]] = t;
    }

    string S;
    cin >> S;

    long long allLeft = 1;

    for (int i = 0; i < N; ++i) {
        int rightNeighbor = (i + 1) % N;

        if (pos[i] < pos[rightNeighbor]) {
            // Both spoons are available.
            // Person i must be left-handed.
            if (S[i] == 'R') {
                allLeft = 0;
            }
        } else {
            // Right spoon is already gone, so left is forced.
            // Either handedness works.
            if (S[i] == '?') {
                allLeft = allLeft * 2 % MOD;
            }
        }
    }

    long long allRight = 1;

    for (int i = 0; i < N; ++i) {
        int leftNeighbor = (i - 1 + N) % N;

        if (pos[i] < pos[leftNeighbor]) {
            // Both spoons are available.
            // Person i must be right-handed.
            if (S[i] == 'L') {
                allRight = 0;
            }
        } else {
            // Left spoon is already gone, so right is forced.
            // Either handedness works.
            if (S[i] == '?') {
                allRight = allRight * 2 % MOD;
            }
        }
    }

    cout << (allLeft + allRight) % MOD << '\n';
}