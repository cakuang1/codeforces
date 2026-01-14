#include <bits/stdc++.h>
using namespace std;

// Fenwick tree: range add / point query
struct Fenwick {
    int n;
    vector<int> bit;
    Fenwick(int n=0): n(n), bit(n+2,0) {}
    void addPoint(int i, int v) {
        for (; i <= n; i += i & -i) bit[i] += v;
    }
    void addRange(int l, int r, int v) {
        addPoint(l, v);
        addPoint(r+1, -v);
    }
    int pointQuery(int i) {
        int s=0;
        for (; i > 0; i -= i & -i) s += bit[i];
        return s;
    }
};

// Aho–Corasick automaton
struct Aho {
    struct Node {
        array<int,26> nxt;
        int link = 0;
        Node() { nxt.fill(-1); }
    };
    vector<Node> t;
    vector<int> term; // terminal node of each pattern
    vector<vector<int>> g;
    vector<int> tin, tout;
    int timer=0;

    Aho() { t.emplace_back(); } // root

    void addPattern(const string &s) {
        int v = 0;
        for (char ch: s) {
            int c = ch - 'a';
            if (t[v].nxt[c] == -1) {
                t[v].nxt[c] = (int)t.size();
                t.emplace_back();
            }
            v = t[v].nxt[c];
        }
        term.push_back(v);
    }

    void build() {
        queue<int> q;
        // set missing root transitions to 0
        for (int c=0;c<26;c++) {
            int u = t[0].nxt[c];
            if (u != -1) {
                t[u].link = 0;
                q.push(u);
            } else {
                t[0].nxt[c] = 0;
            }
        }
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (int c=0;c<26;c++) {
                int u = t[v].nxt[c];
                if (u != -1) {
                    t[u].link = t[t[v].link].nxt[c];
                    q.push(u);
                } else {
                    t[v].nxt[c] = t[t[v].link].nxt[c];
                }
            }
        }

        // build suffix-link tree
        g.assign(t.size(), {});
        for (int v=1; v<(int)t.size(); v++) {
            g[t[v].link].push_back(v);
        }

        // Euler tour
        tin.assign(t.size(), 0);
        tout.assign(t.size(), 0);
        timer=0;
        dfs(0);
    }

    void dfs(int v) {
        tin[v] = ++timer;
        for (int u: g[v]) dfs(u);
        tout[v] = timer;
    }

    long long runText(const string &s, Fenwick &bit) {
        long long ans=0;
        int v=0;
        for (char ch: s) {
            int c = ch - 'a';
            v = t[v].nxt[c];
            ans += bit.pointQuery(tin[v]);
        }
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<string> pat(k);
    for (int i=0; i<k; i++) cin >> pat[i];

    Aho ac;
    for (auto &s: pat) ac.addPattern(s);
    ac.build();

    Fenwick bit(ac.timer);

    // Initially all surnames active
    vector<int> active(k, 1);
    for (int i=0;i<k;i++) {
        int node = ac.term[i];
        bit.addRange(ac.tin[node], ac.tout[node], +1);
    }


    // wewd oesthis rwo werally wor kwdn wrhow to wsoetshwit wr
    // wer
    // itreation wek we= 0 wr
    // sotr subtrings fo length 1 er
    // 
    // cyclic wrsuistrings r
    // wwe will use te n oticio nwer
    while (n--) {
        string q; cin >> q;
        char type = q[0];
        if (type == '+') {
            int idx = stoi(q.substr(1)) - 1;
            if (!active[idx]) {
                active[idx] = 1;
                int node = ac.term[idx];
                bit.addRange(ac.tin[node], ac.tout[node], +1);
            }
        } else if (type == '-') {
            int idx = stoi(q.substr(1)) - 1;
            if (active[idx]) {
                active[idx] = 0;
                int node = ac.term[idx];
                bit.addRange(ac.tin[node], ac.tout[node], -1);
            }
        } else if (type == '?') {
            string txt = q.substr(1);
            cout << ac.runText(txt, bit) << "\n";
        }
    }
    return 0;
}
