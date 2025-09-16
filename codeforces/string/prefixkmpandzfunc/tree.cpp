#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Build prefix-function for pattern t
vector<int> prefix_function(const string &t) {
    int m = (int)t.size();
    vector<int> pi(m, 0);
    for (int i = 1; i < m; i++) {
        int j = pi[i - 1];
        while (j > 0 && t[i] != t[j]) j = pi[j - 1];
        if (t[i] == t[j]) j++;
        pi[i] = j;
    }
    return pi;
}

// Build KMP automaton
vector<vector<int>> build_automaton(const string &t) {
    int m = (int)t.size();
    vector<int> pi = prefix_function(t);
    vector<vector<int>> aut(m + 1, vector<int>(26, 0));

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

struct Edge {
    int to;
    string s;
};

int n;
string pat;
vector<vector<Edge>> g;
ll ans = 0;
int m;
vector<vector<int>> aut;

// DFS with current KMP state
void dfs(int v, int state) {
    for (auto &e : g[v]) {
        int cur = state;
        for (char c : e.s) {
            cur = aut[cur][c - 'a'];
            if (cur == m) ans++;
        }
        dfs(e.to, cur);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    g.assign(n + 1, {});
    for (int v = 2; v <= n; v++) {
        int p;
        string s;
        cin >> p >> s;
        g[p].push_back({v, s});
    }
    cin >> pat;
    m = pat.size();

    aut = build_automaton(pat);

    dfs(1, 0);

    cout << ans << "\n";
    return 0;
}



//strong eatom ato wenr