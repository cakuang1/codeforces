#include <bits/stdc++.h>
using namespace std;

static const int MAXN = 100000;
static int  tree[4*MAXN][26];
static int8_t lazy[4*MAXN];   // -1 = none, 0–25 = letter to assign

int n, m;
string s;

// build [tl..tr]
void build(int v, int tl, int tr) {
    lazy[v] = -1;
    if (tl == tr) {
        memset(tree[v], 0, 26 * sizeof(int));
        tree[v][ s[tl] - 'a' ] = 1;
    } else {
        int tm = (tl + tr) >> 1;
        build(v<<1,   tl,   tm);
        build(v<<1|1, tm+1, tr);
        // pull
        for (int c = 0; c < 26; c++)
            tree[v][c] = tree[v<<1][c] + tree[v<<1|1][c];
    }
}

// assign entire node v to letter c
inline void apply_assign(int v, int tl, int tr, int c) {
    memset(tree[v], 0, 26 * sizeof(int));
    tree[v][c] = tr - tl + 1;
    lazy[v]    = (int8_t)c;
}

void push(int v, int tl, int tr) {
    if (lazy[v] != -1 && tl < tr) {
        int tm = (tl + tr) >> 1;
        apply_assign(v<<1,   tl,   tm, lazy[v]);
        apply_assign(v<<1|1, tm+1, tr, lazy[v]);
        lazy[v] = -1;
    }
}

// range assign [l..r] = c
void update(int v, int tl, int tr, int l, int r, int c) {
    if (l > r) return;
    if (l <= tl && tr <= r) {
        apply_assign(v, tl, tr, c);
        return;
    }
    push(v, tl, tr);
    int tm = (tl + tr) >> 1;
    update(v<<1,   tl,   tm,   l, min(r,tm), c);
    update(v<<1|1, tm+1, tr, max(l,tm+1), r, c);
    // pull
    for (int i = 0; i < 26; i++)
        tree[v][i] = tree[v<<1][i] + tree[v<<1|1][i];
}

// collect frequencies in [l..r] into cnt[26]
void query(int v, int tl, int tr, int l, int r, int cnt[26]) {
    if (l > r) return;
    if (l <= tl && tr <= r) {
        for (int i = 0; i < 26; i++)
            cnt[i] += tree[v][i];
        return;
    }
    push(v, tl, tr);
    int tm = (tl + tr) >> 1;
    if (l <= tm) query(v<<1,   tl,   tm,   l, min(r,tm), cnt);
    if (r  >  tm) query(v<<1|1, tm+1, tr, max(l,tm+1), r,  cnt);
}

// flatten final letters into out[]
void collect_all(int v, int tl, int tr, vector<int> &out) {
    if (tl == tr) {
        for (int c = 0; c < 26; c++) {
            if (tree[v][c]) {
                out[tl] = c;
                break;
            }
        }
    } else {
        push(v, tl, tr);
        int tm = (tl + tr) >> 1;
        collect_all(v<<1,   tl,   tm, out);
        collect_all(v<<1|1, tm+1, tr, out);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    cin >> s;

    build(1, 0, n-1);

    while (m--) {
        int L, R;
        cin >> L >> R;
        --L; --R;

        int cnt[26] = {0};
        query(1, 0, n-1, L, R, cnt);

        // check palindrome feasibility
        int odd = 0, oddChar = -1;
        for (int c = 0; c < 26; c++) {
            if (cnt[c] & 1) {
                oddChar = c;
                if (++odd > 1) break;
            }
        }
        if (odd > 1) continue;

        // build lexicographically smallest palindrome
        vector<int> half(26);
        for (int c = 0; c < 26; c++)
            half[c] = cnt[c] >> 1;

        int idx = L;
        // left half
        for (int c = 0; c < 26; c++) {
            int h = half[c];
            if (!h) continue;
            update(1, 0, n-1, idx, idx + h - 1, c);
            idx += h;
        }
        // middle
        if (oddChar != -1) {
            update(1, 0, n-1, idx, idx, oddChar);
            idx++;
        }
        // right half (reverse)
        for (int c = 25; c >= 0; c--) {
            int h = half[c];
            if (!h) continue;
            update(1, 0, n-1, idx, idx + h - 1, c);
            idx += h;
        }
    }

    // output final string
    vector<int> res(n);
    collect_all(1, 0, n-1, res);
    for (int x : res) 
        cout << char('a' + x);
    cout << "\n";
    return 0;
}//