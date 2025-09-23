#include <bits/stdc++.h>
using namespace std;
const int MOD = 1000000007;
using ll = long long;

struct Node {
    int len, link;
    map<char,int> next;
    int occ; // number of times this palindrome occurs as suffix
    Node(int l=0) : len(l), link(0), occ(0) {}
};

struct Eertree {
    string s;
    vector<Node> tree;
    int suff; // node of longest suffix palindrome

    Eertree(int n) {
        tree.reserve(n+5);
        tree.push_back(Node(-1)); // node 0: imaginary len -1
        tree.push_back(Node(0));  // node 1: empty string
        tree[0].link = 0;
        tree[1].link = 0;
        suff = 1;
    }

    void addChar(char c, int pos, vector<int> &endAt) {
        s.push_back(c);
        int cur = suff;
        while (true) {
            int curlen = tree[cur].len;
            if (pos-1-curlen >= 0 && s[pos-1-curlen] == c) break;
            cur = tree[cur].link;
        }
        if (tree[cur].next.count(c)) {
            suff = tree[cur].next[c];
            tree[suff].occ++;
            endAt[pos]++;
            return;
        }
        int newnode = (int)tree.size();
        tree.push_back(Node(tree[cur].len+2));
        tree[cur].next[c] = newnode;

        if (tree[newnode].len == 1) {
            tree[newnode].link = 1;
        } else {
            int linkcand = tree[cur].link;
            while (true) {
                int candlen = tree[linkcand].len;
                if (pos-1-candlen >= 0 && s[pos-1-candlen] == c) {
                    tree[newnode].link = tree[linkcand].next[c];
                    break;
                }
                linkcand = tree[linkcand].link;
            }
        }
        suff = newnode;
        tree[newnode].occ = 1;
        endAt[pos]++;
    }

    void propagate() {
        // propagate occurrences to suffix links (important if you want counts per node)
        for (int i = (int)tree.size()-1; i >= 2; i--) {
            tree[tree[i].link].occ += tree[i].occ;
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s; 
    cin >> s;
    int n = s.size();

    // Build forward tree to compute endAt
    vector<int> endAt(n, 0);
    {
        Eertree et(n);
        for (int i = 0; i < n; i++) {
            et.addChar(s[i], i, endAt);
        }
    }
    // d oeshtiwwork wer ra ww
    vector<int> startAt(n, 0);
    {
        string rs = s;
        reverse(rs.begin(), rs.end());
        Eertree et(n);
        for (int i = 0; i < n; i++) {
            et.addChar(rs[i], i, startAt);
        }
        reverse(startAt.begin(), startAt.end());
    }


    // machaereswerstate wrs wewhat w
    long long total = 0;
    for (int x : endAt) total += x;
    long long totalPairs = total * (total - 1) / 2;

    // count non-crossing pairs
    long long nonCrossing = 0;
    vector<long long> pref(n+1, 0);
    for (int i = 0; i < n; i++) pref[i+1] = pref[i] + endAt[i];

    for (int i = 0; i < n; i++) {
        nonCrossing += startAt[i] * pref[i];
    }

    cout << totalPairs - nonCrossing << "\n";
}

// no way wethsi wrw wefwerink werwn wefowerax