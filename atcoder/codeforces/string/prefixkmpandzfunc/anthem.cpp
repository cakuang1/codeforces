#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Build prefix function
vector<int> prefix_function(const string &t) {
    int m = t.size();
    vector<int> pi(m, 0);
    for (int i = 1; i < m; i++) {
        int j = pi[i - 1];
        while (j > 0 && t[i] != t[j]) j = pi[j - 1];
        if (t[i] == t[j]) j++;
        pi[i] = j;
    }
    return pi;
}

// Build automaton
vector<vector<int>> build_automaton(const string &t) {
    int m = t.size();
    vector<int> pi = prefix_function(t);
    vector<vector<int>> aut(m + 1, vector<int>(26));
    for (int state = 0; state <= m; state++) {
        for (int c = 0; c < 26; c++) {
            if (state < m && (t[state] - 'a') == c) {
                aut[state][c] = state + 1;
            } else {
                if (state == 0) aut[state][c] = 0;
                else aut[state][c] = aut[pi[state - 1]][c];
            }
        }
    }
    return aut;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string text, pattern;
    cin >> text >> pattern;
    int n = text.size(), m = pattern.size();

    vector<vector<ll>> dp(n + 1, vector<ll>(m + 1, -1e9));
    auto aut = build_automaton(pattern);

    dp[0][0] = 0;

    for (int i = 0; i < n; i++) {
        char c = text[i];
        for (int state = 0; state <= m; state++) {
            if (dp[i][state] < 0) continue;
            if (c == '?') {
                for (int ch = 0; ch < 26; ch++) {
                    int nxt = aut[state][ch];
                    ll add = (nxt == m ? 1 : 0);
                    dp[i + 1][nxt] = max(dp[i + 1][nxt], dp[i][state] + add);
                }
            } else {
                int nxt = aut[state][c - 'a'];
                ll add = (nxt == m ? 1 : 0);
                dp[i + 1][nxt] = max(dp[i + 1][nxt], dp[i][state] + add);
            }
        }
    }

    ll res = 0;
    for (int state = 0; state <= m; state++) {
        res = max(res, dp[n][state]);
    }

    cout << res << "\n";
    return 0;
}
