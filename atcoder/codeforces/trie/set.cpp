#include <bits/stdc++.h>
using namespace std;

struct Trie {
    struct Node {
        int nxt[2];
        int cnt;
        Node() { nxt[0] = nxt[1] = -1; cnt = 0; }
    };
    vector<Node> t;
    Trie() { t.emplace_back(); }  // root

    void insert(int x, int delta) {
        int v = 0;
        for (int b = 29; b >= 0; b--) {
            int c = (x >> b) & 1;
            if (t[v].nxt[c] == -1) {
                t[v].nxt[c] = t.size();
                t.emplace_back();
            }
            v = t[v].nxt[c];
            t[v].cnt += delta;
        }
    }

    void add(int x) { insert(x, +1); }
    void remove(int x) { insert(x, -1); }

    int queryMinXor(int x) {
        int v = 0, res = 0;
        for (int b = 29; b >= 0; b--) {
            int c = (x >> b) & 1;
            // Prefer same branch if exists and has count > 0
            if (t[v].nxt[c] != -1 && t[t[v].nxt[c]].cnt > 0) {
                v = t[v].nxt[c];
            } else {
                v = t[v].nxt[c ^ 1];
                res |= (1 << b);
            }
        }
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int Q; cin >> Q;
    Trie trie;

    while (Q--) {
        int type, x;
        cin >> type >> x;
        if (type == 0) {
            trie.add(x);
        } else if (type == 1) {
            trie.remove(x);
        } else {
            cout << trie.queryMinXor(x) << "\n";
        }
    }
}
