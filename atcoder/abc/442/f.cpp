#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> dp(N + 1, 0), ndp(N + 1);
    vector<int> suf(N + 1);

    for (int i = 0; i < N; i++) {
        string s;
        cin >> s;

        suf[N] = dp[N];
        for (int j = N - 1; j >= 0; j--) suf[j] = min(dp[j], suf[j + 1]);

        // split k = 0: whole row should be '#'
        // flips = number of '.' that must be turned into '#'
        int cost = 0;
        for (char c : s) if (c == '.') cost++;

        ndp[0] = cost + suf[0];

        for (int j = 0; j < N; j++) {
            // moving boundary past column j:
            // that cell changes from right side (# expected) to left side (. expected)
            // if s[j] == '#': was correct, becomes wrong -> +1
            // if s[j] == '.': was wrong, becomes correct -> -1
            cost += (s[j] == '#') ? 1 : -1;
            ndp[j + 1] = cost + suf[j + 1];
        }

        dp.swap(ndp);
    }

    cout << *min_element(dp.begin(), dp.end()) << "\n";
    return 0;
}