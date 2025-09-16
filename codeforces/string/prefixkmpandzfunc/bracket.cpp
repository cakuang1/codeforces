#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MOD = 1000000007;

// Prefix function
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

// Automaton builder for '(' and ')'
vector<vector<int>> build_automaton(const string &t) {
    int m = t.size();
    vector<int> pi = prefix_function(t);
    vector<vector<int>> aut(m + 1, vector<int>(2));
    auto encode = [](char c) { return (c == '(' ? 0 : 1); };
    for (int state = 0; state <= m; state++) {
        for (int c = 0; c < 2; c++) {
            if (state < m && encode(t[state]) == c) {
                aut[state][c] = state + 1;
            } else {
                if (state == 0) aut[state][c] = 0;
                else aut[state][c] = aut[pi[state - 1]][c];
            }
        }
    }
    return aut;
}

ll dp[201][101][201][2];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    string s;
    cin >> n >> s;
    int m = s.size();

    auto nxt = build_automaton(s);

    dp[0][0][0][0] = 1;

    for (int pos = 0; pos < 2 * n; pos++) {
        for (int open = 0; open <= n; open++) {
            for (int state = 0; state <= m; state++) {
                for (int seen = 0; seen < 2; seen++) {
                    ll cur = dp[pos][open][state][seen];
                    if (!cur) continue;

                    // add '('
                    if (open + 1 <= n) {
                        int ns = nxt[state][0];
                        int nsSeen = seen | (ns == m);
                        dp[pos + 1][open + 1][ns][nsSeen] =
                            (dp[pos + 1][open + 1][ns][nsSeen] + cur) % MOD;
                    }
                    // add ')'
                    if (open > 0) {
                        int ns = nxt[state][1];
                        int nsSeen = seen | (ns == m);
                        dp[pos + 1][open - 1][ns][nsSeen] =
                            (dp[pos + 1][open - 1][ns][nsSeen] + cur) % MOD;
                    }
                }
            }
        }
    }

    ll ans = 0;
    for (int state = 0; state <= m; state++) {
        ans = (ans + dp[2 * n][0][state][1]) % MOD;
    }
    cout << ans << "\n";
    return 0;
}
