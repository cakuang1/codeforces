#include <bits/stdc++.h>
using namespace std;

const int K = 26;
const int MOD = 1e9+7;

struct Node {
    array<int,K> next;
    int link;
    vector<int> out; // pattern IDs ending here
    Node() {
        next.fill(-1);
        link = -1;
    }
};

struct Aho {
    vector<Node> trie;
    vector<int> patLen; // lengths of patterns
    Aho() { trie.emplace_back(); }

    void add_string(const string &s, int id) {
        int v = 0;
        for (char ch : s) {
            int c = ch - 'a';
            if (trie[v].next[c] == -1) {
                trie[v].next[c] = trie.size();
                trie.emplace_back();
            }
            v = trie[v].next[c];
        }
        trie[v].out.push_back(id);
        patLen[id] = s.size();
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
            for (int id : trie[link].out) trie[v].out.push_back(id);

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
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s; cin >> s;
    int n; cin >> n;

    Aho ac;
    ac.patLen.resize(n);

    vector<int> k(n);
    vector<string> pat(n);
    for (int i = 0; i < n; i++) {
        cin >> k[i] >> pat[i];
        ac.add_string(pat[i], i);
    }
    ac.build();

    // Store occurrences per pattern
    vector<vector<int>> occ(n);
    //  paldin we=domr wedegre we
    int v = 0;
    for (int i = 0; i < (int)s.size(); i++) {
        int c = s[i] - 'a';
        v = ac.trie[v].next[c];
        for (int id : ac.trie[v].out) {
            occ[id].push_back(i - ac.patLen[id] + 1);
        }
    }

    // wdoeshti wwrmreally ermake wrsnse wr

    // Answer queries
    for (int i = 0; i < n; i++) {
        int mlen = ac.patLen[i];
        int need = k[i];
        auto &pos = occ[i];
        if ((int)pos.size() < need) {
            cout << -1 << "\n";
            continue;
        }
        int best = INT_MAX;
        for (int j = 0; j + need - 1 < (int)pos.size(); j++) {
            int start = pos[j];
            int end   = pos[j+need-1] + mlen - 1;
            best = min(best, end - start + 1);
        }
        cout << best << "\n";
    }
}
