#include <bits/stdc++.h>
using namespace std;
#include <bits/stdc++.h>
using namespace std;

struct SegTree {
    int n;
    vector<vector<int>> tree;  // Each node has vector<int>(26)
    vector<int> lazy;  // -1 means no assignment pending, 0-25 means assign that value

    SegTree(const vector<int> &a) {
        n = a.size();
        tree.assign(4*n, vector<int>(26, 0));
        lazy.assign(4*n, -1);
        build(1, 0, n-1, a);
    }

    void build(int v, int tl, int tr, const vector<int> &a) {
        if (tl == tr) {
            tree[v][ a[tl] ] = 1;
        } else {
            int tm = (tl + tr) >> 1;
            build(v<<1,   tl,   tm, a);
            build(v<<1|1, tm+1, tr, a);
            pull(v);
        }
    }

    void apply_assign(int v, int tl, int tr, int c) {
        fill(tree[v].begin(), tree[v].end(), 0);
        tree[v][c] = (tr - tl + 1);
        lazy[v] = c;
    }

    void push(int v, int tl, int tr) {
        if (lazy[v] != -1 && tl != tr) {
            int tm = (tl + tr) >> 1;
            apply_assign(v<<1,   tl,   tm, lazy[v]);
            apply_assign(v<<1|1, tm+1, tr, lazy[v]);
            lazy[v] = -1;
        }
    }

    void pull(int v) {
        for (int i = 0; i < 26; i++) {
            tree[v][i] = tree[v<<1][i] + tree[v<<1|1][i];
        }
    }

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
        pull(v);
    }

    vector<int> query(int v, int tl, int tr, int l, int r) {
        if (l > r) return vector<int>(26, 0);
        if (l <= tl && tr <= r) return tree[v];
        push(v, tl, tr);
        int tm = (tl + tr) >> 1;
        auto left  = query(v<<1,   tl,   tm,   l, min(r,tm));
        auto right = query(v<<1|1, tm+1, tr, max(l,tm+1), r);
        vector<int> res(26);
        for (int i = 0; i < 26; i++) res[i] = left[i] + right[i];
        return res;
    }

    void update(int l, int r, int c) { update(1,0,n-1,l,r,c); }
    vector<int> query(int l, int r) { return query(1,0,n-1,l,r); }

    void collect(int v, int tl, int tr, vector<int> &out) {
        if (tl == tr) {
            for (int i = 0; i < 26; i++) {
                if (tree[v][i]) { out[tl] = i; break; }
            }
        } else {
            push(v, tl, tr);
            int tm = (tl + tr) >> 1;
            collect(v<<1,   tl,   tm, out);
            collect(v<<1|1, tm+1, tr, out);
        }
    }
    
    vector<int> final_array() {
        vector<int> out(n);
        collect(1, 0, n-1, out);
        return out;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    vector<int> a(n);
    for (int i = 0; i < n; i++) a[i] = s[i] - 'a';
    // output the final
    SegTree st(a);
    while(q--) {
        int  l, r, type;
        cin >>l >> r >> type; 

        l --; r --;
        vector<int> counts =  st.query(l,r);
        int left = l; 
        if(type == 1) {
            for (int i = 0  ; i < 26; i ++) {
                if (counts[i]) {
                    st.update(left,left + counts[i] - 1, i);
                    left = left + counts[i];
                }
            }
        } else {
            for (int i = 25 ; i >= 0 ; i --) {
                if (counts[i]) {
                    st.update(left,left + counts[i] - 1, i);
                    left = left + counts[i];
                }
            }
        }
    }
    
    auto res = st.final_array();
    for (int i = 0; i < n; i++) cout << char('a' + res[i]);
    cout << '\n';
    return 0;
}



