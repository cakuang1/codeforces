#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    string S, T;
    cin >> S >> T;

    vector<int> cnt(10, 0);

    for (char c : T) {
        cnt[c - '0']++;
    }

    // First ignore the "T[M-1] must survive" condition.
    // Greedily improve S from left to right.
    for (int i = 0; i < N; ++i) {
        int cur = S[i] - '0';

        for (int d = 9; d > cur; --d) {
            if (cnt[d] > 0) {
                S[i] = char('0' + d);
                cnt[d]--;
                break;
            }
        }
    }

    // The last operation T[M-1] must appear in the final string.
    char must = T[M - 1];

    bool exists = false;
    for (char c : S) {
        if (c == must) {
            exists = true;
            break;
        }
    }

    // If it doesn't appear, force it into the least significant position.
    if (!exists) {
        S[N - 1] = must;
    }

    cout << S << '\n';
    return 0;
}




// wesdo who wos w