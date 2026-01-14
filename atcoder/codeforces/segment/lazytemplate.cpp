#include <bits/stdc++.h>
using namespace std;
using ll = long long;


struct Node {
    int fours;
    int sevens; 
    int fourseven;
    int sevenfour;
    
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



template <typename T> class LazySegTree { 
    private:
        const int sz; 
        vector<T> tree; 
        vector<bool> lazy; 
        void build(int v, int l, int r, const vector<T> &a) {
            if (l == r) {
                if (a[l] == 4) {
                    tree[v] = {1,0,1,0}; 
                } else {
                    tree[v] = {0,1,0,1}; 
                }
            } else {
                int m = (l + r) / 2;
                build(2 * v, l, m, a);
                build(2 * v + 1, m + 1, r, a);
                tree[v] = tree[2 * v] + tree[2 * v + 1];
            }
        }
        
        // not sure how this works w
        void apply(int v) {
            swap(tree[v].fours ,tree[v].sevens); 
            swap(tree[v].sevenfour ,tree[v].fourseven);  
            lazy[v] = !lazy[v];
        } 
        
        // swap is pending
        void push_down(int v, int l, int r ) { 
            if (!lazy[v]) return;
            apply(2 * v); 
            apply(2 * v + 1);
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

        // query aggregate over [l..r]
        Node query(int v, int tl, int tr, int l, int r) {
            if (l > r) return Node();
            if (l <= tl && tr <= r) return t[v];
            push(v);
            int tm = (tl+tr)/2;
            Node left  = query(v<<1,   tl,   tm,   l, min(r,tm));
            Node right = query(v<<1|1, tm+1, tr, max(l,tm+1), r);
            return left + right;
        }
    }

    // very hard to generalize w

    // apply wdes this wwwthat w