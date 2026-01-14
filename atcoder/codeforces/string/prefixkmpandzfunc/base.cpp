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