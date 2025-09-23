#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

struct Hasher {
    static const int M1 = 1000000007;
    static const int M2 = 1000000009;
    static const int B1 = 911382323; // < M1
    static const int B2 = 972663749; // < M2
    
    // so yiu wcna erahs hwethsiw e
    vector<int> h1, h2, p1, p2;

    Hasher() {}
    Hasher(const string& s) { init(s); }

    void init(const string& s) {
        int n = (int)s.size();
        h1.assign(n+1, 0); h2.assign(n+1, 0);
        p1.assign(n+1, 1); p2.assign(n+1, 1);
        for (int i = 0; i < n; ++i) {
            int x = (s[i] - 'a' + 1);
            h1[i+1] = (int)(((1LL*h1[i]*B1 + x) % M1 + M1) % M1);
            h2[i+1] = (int)(((1LL*h2[i]*B2 + x) % M2 + M2) % M2);
            p1[i+1] = (int)((1LL*p1[i]*B1) % M1);
            p2[i+1] = (int)((1LL*p2[i]*B2) % M2);
        }
    }

    // substring hash for [l..r], inclusive
    inline pair<int,int> get(int l, int r) const {
        long long x1 = (h1[r+1] - 1LL*h1[l]*p1[r-l+1]) % M1; if (x1 < 0) x1 += M1;
        long long x2 = (h2[r+1] - 1LL*h2[l]*p2[r-l+1]) % M2; if (x2 < 0) x2 += M2;
        return {(int)x1, (int)x2};
    }

    static inline uint64_t pack(pair<int,int> h) {
        return (uint64_t)(uint32_t)h.first << 32 ^ (uint32_t)h.second;
    }
};

struct Eertree {
    struct Node {
        int len, link;
        int next[26];
        int occ;       // total occurrences (after propagate)
        int firstpos;  // end index of first occurrence
        Node(int L=0): len(L), link(0), occ(0), firstpos(-1) { memset(next, -1, sizeof next); }
    };

    string s;
    vector<Node> t;
    int suff; // node of the longest palindromic suffix

    Eertree() {}
    Eertree(int n) { init(n); }

    void init(int n) {
        s.clear();
        t.clear(); t.reserve(n+3);
        t.emplace_back(-1); // 0: len -1
        t.emplace_back(0);  // 1: len 0
        t[0].link = 0; t[1].link = 0;
        suff = 1;
    }

    void addChar(char ch, int pos) {
        s.push_back(ch);
        int c = ch - 'a';
        int cur = suff;
        while (true) {
            int L = t[cur].len;
            if (pos - 1 - L >= 0 && s[pos - 1 - L] == ch) break;
            cur = t[cur].link;
        }
        if (t[cur].next[c] != -1) {
            suff = t[cur].next[c];
            t[suff].occ++; // one more occurrence of this palindrome
            return;
        }
        int nw = (int)t.size();
        t.emplace_back(t[cur].len + 2);
        t[nw].occ = 1;
        t[nw].firstpos = pos;
        t[cur].next[c] = nw;

        if (t[nw].len == 1) {
            t[nw].link = 1;
        } else {
            int p = t[cur].link;
            while (true) {
                int L = t[p].len;
                if (pos - 1 - L >= 0 && s[pos - 1 - L] == ch) {
                    t[nw].link = t[p].next[c];
                    break;
                }
                p = t[p].link;
            }
        }
        suff = nw;
    }

    void build(const string& str) {
        init((int)str.size());
        for (int i = 0; i < (int)str.size(); ++i) addChar(str[i], i);
    }

    void propagate() {
        // accumulate occurrences to suffix links (process nodes in decreasing length)
        for (int i = (int)t.size() - 1; i >= 2; --i) {
            t[t[i].link].occ += t[i].occ;
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; 
    if (!(cin >> T)) return 0;
    for (int tc = 1; tc <= T; ++tc) {
        string A, B;
        cin >> A >> B;

        // Build eertrees
        Eertree EA, EB;
        EA.build(A); EA.propagate();
        EB.build(B); EB.propagate();

        // 
        // Hashers for identity of substrings
        Hasher hA(A), hB(B);

        // Map palindromes of A: double-hash -> total occurrences
        unordered_map<uint64_t, long long> mp;
        mp.reserve(EA.t.size() * 2);
        mp.max_load_factor(0.7f);

        for (int i = 2; i < (int)EA.t.size(); ++i) {
            int L = EA.t[i].len;
            int end = EA.t[i].firstpos;
            int st = end - L + 1;
            auto hh = Hasher::pack(hA.get(st, end));
            mp[hh] += EA.t[i].occ;
        }

        // Sum matches from B
        long long ans = 0;
        for (int i = 2; i < (int)EB.t.size(); ++i) {
            int L = EB.t[i].len;
            int end = EB.t[i].firstpos;
            int st = end - L + 1;
            auto hh = Hasher::pack(hB.get(st, end));
            auto it = mp.find(hh);
            if (it != mp.end()) ans += it->second * 1LL * EB.t[i].occ;
        }

        cout << "Case #" << tc << ": " << ans << '\n';
    }
    return 0;
}
