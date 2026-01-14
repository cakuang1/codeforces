#include <bits/stdc++.h>
using namespace std;

struct Node {
    int fours, sevens;
    int fourseven, sevenfour;
    Node(): fours(0), sevens(0), fourseven(0), sevenfour(0) {}
    Node(int f,int s,int fs,int sf)
      : fours(f), sevens(s), fourseven(fs), sevenfour(sf) {}

    // combine two child‐nodes
    Node operator+(const Node &b) const {
        Node r;
        r.fours     = fours + b.fours;
        r.sevens    = sevens + b.sevens;
        r.fourseven = max({ fourseven,
                            b.fourseven,
                            fours + b.fourseven,
                            fourseven + b.sevens });
        r.sevenfour = max({ sevenfour,
                            b.sevenfour,
                            sevens + b.sevenfour,
                            sevenfour + b.fours });
        return r;
    }
};

struct SegTree {
    int n;
    vector<Node>  t;
    vector<bool>  lazy;

    SegTree(const string &s) {
        n = s.size();
        t.resize(4*n);
        lazy.assign(4*n, false);
        build(1, 0, n-1, s);
    }

    void build(int v, int tl, int tr, const string &s) {
        if (tl == tr) {
            // leaf: either '4' or '7'
            if (s[tl] == '4') t[v] = Node(1,0,1,0);
            else              t[v] = Node(0,1,0,1);
        } else {
            int tm = (tl+tr)/2;
            build(v<<1,   tl,   tm, s);
            build(v<<1|1, tm+1, tr, s);
            t[v] = t[v<<1] + t[v<<1|1];
        }
    }

    // apply a swap to node v
    void apply(int v) {
        swap(t[v].fours,     t[v].sevens);
        swap(t[v].fourseven, t[v].sevenfour);
        lazy[v] = !lazy[v];
    }

    // push pending lazy flag to children
    void push(int v) {
        if (!lazy[v]) return;
        apply(v<<1);
        apply(v<<1|1);
        lazy[v] = false;
    }

    // flip range [l..r]
    void update(int v, int tl, int tr, int l, int r) {
        if (l > r) return;
        if (l <= tl && tr <= r) {
            apply(v);
            return;
        }
        push(v);
        int tm = (tl+tr)/2;
        if (l <= tm)     update(v<<1,   tl,   tm,   l, min(r,tm));
        if (r >  tm)     update(v<<1|1, tm+1, tr, max(l,tm+1), r);
        t[v] = t[v<<1] + t[v<<1|1];
    }

    Node query(int v, int tl, int tr, int l, int r) {
        if (l > r) return Node();
        if (l <= tl && tr <= r) return t[v];
        push(v);
        int tm = (tl+tr)/2;
        Node left  = query(v<<1,   tl,   tm,   l, min(r,tm));
        Node right = query(v<<1|1, tm+1, tr, max(l,tm+1), r);
        return left + right;
    }
    void update(int l, int r) {
        update(1, 0, n-1, l, r);
    }
    Node query() {
        return query(1, 0, n-1, 0, n-1);
    }
    Node query(int l, int r) {
        return query(1, 0, n-1, l, r);
    }

};
    int  main() {
        ios_base::sync_with_stdio(0); cin.tie(0);  
        int n, m; cin >> n >> m ;
        string s ; cin >> s;
        SegTree st(s); 
        while (m--) {
            string op;
            cin >> op;
            if (op == "count") {
                auto R = st.query();
                cout << max({R.fourseven, R.fours, R.sevens}) << "\n";
            } else {
                int a, b;
                cin >> a >> b;
                a --;
                b --;
                st.update(a, b);
            }
        }
        return 0; 
    }


    