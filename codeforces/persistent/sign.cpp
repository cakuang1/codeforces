

    #include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Node {
    ll sum;       // sum over this segment
    ll lazy;      // pending increment to propagate
    Node *l, *r;
    Node(ll _sum=0, ll _lazy=0, Node* _l=nullptr, Node* _r=nullptr)
      : sum(_sum), lazy(_lazy), l(_l), r(_r) {}
};

int N;             // size of the array, [1..N]
vector<Node*> root;  // root[i] = version after i updates

// Build an all-zero tree over [tl..tr]
Node* build(int tl, int tr) {
    Node* n = new Node();
    if (tl == tr) return n;
    int tm = (tl+tr)>>1;
    n->l = build(tl, tm);
    n->r = build(tm+1, tr);
    return n;
}

// Apply an increment v to node n covering [tl..tr]
inline void apply(Node* n, int tl, int tr, ll v) {
    n->sum  += v * (tr - tl + 1);
    n->lazy += v;
}

// Clone node p and return the new copy
inline Node* clone(Node* p) {
    return new Node(p->sum, p->lazy, p->l, p->r);
}

// Range-add v on [l..r], starting from old version cur, returns new root
Node* update(Node* cur, int tl, int tr, int l, int r, ll v) {
    if (r < tl || tr < l) 
        return cur;  // no change, share node
    Node* n = clone(cur);
    if (l <= tl && tr <= r) {
        apply(n, tl, tr, v);
        return n;
    }
    int tm = (tl+tr)>>1;
    // push lazy to children
    if (n->lazy) {
        n->l = clone(n->l);
        n->r = clone(n->r);
        apply(n->l, tl, tm, n->lazy);
        apply(n->r, tm+1, tr, n->lazy);
        n->lazy = 0;
    }
    n->l = update(n->l, tl, tm, l, r, v);
    n->r = update(n->r, tm+1, tr, l, r, v);
    n->sum = n->l->sum + n->r->sum;
    return n;
}

// Range-sum query over [l..r] on version cur
ll query(Node* cur, int tl, int tr, int l, int r) {
    if (!cur || r < tl || tr < l) return 0;
    if (l <= tl && tr <= r) return cur->sum;
    int tm = (tl+tr)>>1;
    // we don't clone or modify on query; children sums already include lazy
    return query(cur->l, tl, tm, l, r)
         + query(cur->r, tm+1, tr, l, r);
}




//
    struct  F  {
        ll x1,x2,y1,a,b,y2; 
    }
    int main()  {
        ios_base::sync_with_stdio(0); cin.tie(0);  
        int n ; cin >> n;
        vector<F> arr(n);
        for (int i = 0 ; i < n; i ++) {
            cin >> arr[i].x1 >> arr[i].x2 >> arr[i].y1 >> arr[i].a >> arr[i].b >> arr[i].y2;
        }        
        
        // in this segment  weewdoesth is really wwor kww e
        
        // wewewdetmeirnw erquetsi weand hwo to see this w wfor wt wer
    
        // detemrine from l - r the sum of allws 
        // wtwo major wupdates w


        vector<Node*> ksum; 
        vector<Node*> c;  
        int querymax  = 200005; 
        ksum .resize(querymax); 
        c.resize(querymax);
        ksum[0] = build(0 ,querymax); 
        c[0] = build(0,querymax);
        
        for (int i = 1 ; i <= n; i ++) {
            int x1  = arr[i].x1;
            int x2  = arr[i].x2;
            int y1  = arr[i].y1;
            int a  = arr[i].a;
            int b = arr[i].b;
            int y2   = arr[i].y2;
            auto tmp = c.back(); 
            // [0,x1] y1
            tmp = update(tmp , 0, querymax - 1,0, x1 ,y1 ); 
            //  [x2 + 1, end] y2; 
            tmp = update(tmp , 0, querymax - 1,x2, querymax - 1  ,y2 ); 
            // [x1 + 1 , x2 ]  b;
            tmp = update(tmp , 0, querymax - 1,x1 + 1 , x2  ,b ); 
            c[i] = tmp; 
            
            auto tmp2 = ksum.back(); 
            tmp2 = update(tmp2 , 0, querymax - 1,x1 + 1 , x2  ,a); 
            ksum[i] = tmp2; 
        } 



        int m; cin >> m; 
        ll last = 0; 
        for (int i = 0 ; i < m ; i ++) {
            ll  l,r,x ;
            cin >> l >> r >> x;
            x = (last + x) % mod;
            ll kpart = query(ksum [r],0,querymax  - 1, x,x)  -  query(ksum[l - 1],0,querymax  - 1, x,x); 
            ll cpart = query(c[r],0,querymax  - 1, x,x)  -  query(c[l - 1],0,querymax  - 1, x,x); 
            ll res = (kpart * x) + cpart; 
            cout << res << endl; 
        }
            

        return 0;
    }
