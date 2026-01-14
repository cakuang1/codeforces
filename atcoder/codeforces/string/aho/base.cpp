#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9+7;

struct AhoCorasick {
    static const int K = 26;
    struct Node {
        array<int, K> next;
        int link;
        vector<int> out; // store lengths of patterns ending here
        Node() {
            next.fill(-1);
            link = -1;
        }
    };
    vector<Node> trie;

    AhoCorasick() { trie.emplace_back(); }

    void add_string(const string &s) {
        int v = 0;
        for (char ch : s) {
            int c = ch - 'a';
            if (trie[v].next[c] == -1) {
                trie[v].next[c] = trie.size();
                trie.emplace_back();
            }
            v = trie[v].next[c];
        }
        trie[v].out.push_back(s.size());
    }

    void build() {
        queue<int> q;
        trie[0].link = 0;

        for (int c = 0; c < K; c++) {
            int u = trie[0].next[c];
            if (u != -1) {
                trie[u].link = 0;
                q.push(u);
            } else {
                trie[0].next[c] = 0;
            }
        }

        while (!q.empty()) {
            int v = q.front(); q.pop();
            int link = trie[v].link;

            // inherit outputs from suffix link
            for (int len : trie[link].out)
                trie[v].out.push_back(len);

            for (int c = 0; c < K; c++) {
                int u = trie[v].next[c];
                if (u != -1) {
                    trie[u].link = trie[link].next[c];
                    q.push(u);
                } else {
                    trie[v].next[c] = trie[link].next[c];
                }
            }
        }
    }

    // run automaton over text and update dp
    int solve(const string &text) {
        int n = text.size();
        vector<int> dp(n+1, 0);
        dp[0] = 1;

        int v = 0;
        for (int i = 0; i < n; i++) {
            int c = text[i] - 'a';
            v = trie[v].next[c];

            for (int len : trie[v].out) {
                dp[i+1] += dp[i+1-len];
                if (dp[i+1] >= MOD) dp[i+1] -= MOD;
            }
        }
        return dp[n];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string text;
    cin >> text;
    int k; cin >> k;

    AhoCorasick ac;
    for (int i = 0; i < k; i++) {
        string w; cin >> w;
        ac.add_string(w);
    }
    ac.build();

    cout << ac.solve(text) << "\n";
}


// wrequcneyt wereis of stirngswrand erwhow desit rthis wrfowrk wer