#include <bits/stdc++.h>
using namespace std;

struct Point { int x, y; };

// A simple kd‐tree for Manhattan‐nearest‐neighbor
struct KDTree {
    struct Node {
        Point p;
        int mnx, mxx, mny, mxy;
        Node *l, *r;
        Node(const Point& _p)
          : p(_p), mnx(_p.x), mxx(_p.x),
            mny(_p.y), mxy(_p.y),
            l(NULL), r(NULL) {}
    };

    Node* root = NULL;

    // Build [l,r) splitting on dimension d (0=x,1=y)
    Node* build(vector<Point>& pts, int l, int r, int d) {
        if (l >= r) return NULL;
        int m = (l + r) >> 1;
        nth_element(pts.begin()+l, pts.begin()+m, pts.begin()+r,
                    [d](const Point& A, const Point& B){
                        return d==0 ? A.x < B.x : A.y < B.y;
                    });
        Node* nd = new Node(pts[m]);
        nd->l = build(pts, l,  m, d^1);
        nd->r = build(pts, m+1, r, d^1);
        // pull up bounding‐box from children
        if (nd->l) {
            nd->mnx = min(nd->mnx, nd->l->mnx);
            nd->mxx = max(nd->mxx, nd->l->mxx);
            nd->mny = min(nd->mny, nd->l->mny);
            nd->mxy = max(nd->mxy, nd->l->mxy);
        }
        if (nd->r) {
            nd->mnx = min(nd->mnx, nd->r->mnx);
            nd->mxx = max(nd->mxx, nd->r->mxx);
            nd->mny = min(nd->mny, nd->r->mny);
            nd->mxy = max(nd->mxy, nd->r->mxy);
        }
        return nd;
    }

    void build(vector<Point>& pts) {
        root = build(pts, 0, (int)pts.size(), 0);
    }

    // Manhattan distance point→point
    static inline int distP(const Point& a, const Point& b) {
        return abs(a.x - b.x) + abs(a.y - b.y);
    }
    // Lower‐bound Manhattan distance point→box
    static inline int distB(const Point& q, Node* nd){
        int dx = 0, dy = 0;
        if      (q.x < nd->mnx) dx = nd->mnx - q.x;
        else if (q.x > nd->mxx) dx = q.x - nd->mxx;
        if      (q.y < nd->mny) dy = nd->mny - q.y;
        else if (q.y > nd->mxy) dy = q.y - nd->mxy;
        return dx + dy;
    }

    void query(Node* nd, const Point& q, int& best) {
        if (!nd) return;
        // prune if even box‐distance >= best
        int dbox = distB(q, nd);
        if (dbox >= best) return;
        // check this node’s point
        best = min(best, distP(q, nd->p));
        // choose child order by which box is closer
        int dl = nd->l ? distB(q, nd->l) : INT_MAX;
        int dr = nd->r ? distB(q, nd->r) : INT_MAX;
        if (dl < dr) {
            if (dl < best) query(nd->l, q, best);
            if (dr < best) query(nd->r, q, best);
        } else {
            if (dr < best) query(nd->r, q, best);
            if (dl < best) query(nd->l, q, best);
        }
    }

    // returns nearest‐neighbor L1 distance
    int nearest(const Point& q) {
        int best = INT_MAX;
        query(root, q, best);
        return best;
    }
};



int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr 
        #include <bits/stdc++.h>
        
        using namespace std;
    
        using ll = long long;
        const int MOD = 1000000007; 
        const int MOD2 =  998244353; 
        const ll INF = 1e18;
        const int MX = 1000001; //check the limits, dummy
    
    
    
        // sqaur
        ll modExp(ll base, ll power) {
            if (power == 0) {
                return 1;
            } else {
                ll cur = modExp(base, power / 2); cur = cur * cur; cur = cur % MOD;
                if (power % 2 == 1) cur = cur * base;
                cur = cur % MOD;
                return cur;
            }
        }
        
        ll inv(ll base) {
            return modExp(base, MOD-2);
        }
    
        // does thi eweralmreally ermake any wesnsee wer
        ll mul(ll A, ll B) {
            return (A*B)%MOD;
        }
    
        ll add(ll A, ll B) {
            return (A+B)%MOD;
        }
        ll dvd(ll A, ll B) {
            return mul(A, inv(B));
        }
    
        ll sub(ll A, ll B) {
            return (A-B+MOD)%MOD;
        }
        ll cielDiv(ll A , ll B) {
            return (A + B - 1)/B;
        } 
    
        ll* facs = new ll[MX];
        ll* facInvs = new ll[MX];
        ll choose(ll a, ll b) {
            if (b > a) return 0;
            if (a < 0) return 0;
            if (b < 0) return 0;
            ll cur = facs[a];
            cur = mul(cur, facInvs[b]);
            cur = mul(cur, facInvs[a-b]);
            return cur;
        }
        
        
        void initFacs() {
            facs[0] = 1; 
            facInvs[0] = 1;
            for (int i = 1 ; i < MX ; i ++ ) {
                facs[i] = (facs[i-1] * i) % MOD;
                facInvs[i] = inv(facs[i]);
            }
        }
        // fdin the oconjecteinrue and thd oth eht
        int main()  {
            ios_base::sync_with_stdio(0); cin.tie(0);  
            return 0;
        }
    );

    int n, m;
    cin >> n >> m;

    vector<Point> reserved(n), freept(m);
    for(int i = 0; i < n; i++){
        cin >> reserved[i].x >> reserved[i].y;
    }
    for(int i = 0; i < m; i++){
        cin >> freept[i].x >> freept[i].y;
    }

    KDTree tree;
    tree.build(reserved);

    int answer = 0;
    for(auto &f : freept){
        int d = tree.nearest(f);
        answer = max(answer, d);
    }
    cout << answer << "\n";
    return 0;
}
// ww
