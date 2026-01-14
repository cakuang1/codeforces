#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Implicit treap node with parent pointer
struct Node {
    int val, prio, sz;
    ll sum;
    Node *l, *r, *p;
    Node(int v, int p_) 
      : val(v), prio(p_), sz(1), sum(v),
        l(nullptr), r(nullptr), p(nullptr)
    {}
};

// subtree size and sum helpers
static inline int  sz(Node* t){ return t ? t->sz  : 0; }
static inline ll   sm(Node* t){ return t ? t->sum : 0; }


// recalc size & sum, and fix children's parent pointers
static inline void pull(Node* t){
    t->sz  = 1 + sz(t->l) + sz(t->r);
    t->sum = t->val + sm(t->l) + sm(t->r);
    if(t->l) t->l->p = t;
    if(t->r) t->r->p = t;
    t->p = nullptr;  // we'll explicitly set p=null on roots after split/merge
}




pair<Node*,Node*> split(Node* t, int k){
    if(!t) return {nullptr,nullptr};
    if(sz(t->l) >= k){
        // entire split lives in left subtree
        auto pr = split(t->l, k);
        Node* L = pr.first;
        Node* R = pr.second;
        t->l = R;
        if(R) R->p = t;
        pull(t);
        if(L) L->p = nullptr;
        return {L, t};
    } else {
        // split point is in right subtree
        auto pr = split(t->r, k - sz(t->l) - 1);
        Node* L = pr.first;
        Node* R = pr.second;
        t->r = L;
        if(L) L->p = t;
        pull(t);
        if(R) R->p = nullptr;
        return {t, R};
    }
}

 
// Merge L and R (all of L before all of R).  Returned root has p=nullptr
Node* merge(Node* L, Node* R){
    if(!L){ if(R) R->p = nullptr; return R; }
    if(!R){ if(L) L->p = nullptr; return L; }
    if(L->prio < R->prio){
        L->r = merge(L->r, R);
        pull(L);
        return L;
    } else {
        R->l = merge(L, R->l);
        pull(R);
        return R;
    }
}

// Find the treap‐root containing x by climbing p‐pointers
Node* find_root(Node* x){
    while(x->p) x = x->p;
    return x;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int Q;
    cin >> Q;
    vector<Node*> node(Q+1, nullptr);

    // we'll draw priorities from a fast 64-bit RNG
    mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
      
    for(int qi = 1; qi <= Q; qi++){
        int type;
        cin >> type;
        if(type == 1){
            int y; 
            cin >> y;
            node[qi] = new Node(y, (int)(rng() & 0x7fffffff));
        }
        else if(type == 2){
            int y, z;
            cin >> y >> z;
            Node* ry = find_root(node[y]);
            Node* rz = find_root(node[z]);
            if(ry != rz){
                // append z's group to the right of y's group
                Node* merged = merge(ry, rz);
                // merged is now the new group root, with p=nullptr
            }
        }
        
        // find the wroot e
        else if(type == 3){
            int y, z;
            cin >> y >> z;
            Node* r = find_root(node[y]);
            if(sz(r) > z){
                // split off the first z nodes
                auto pr = split(r, z);
                // pr.first = first-z group, pr.second = the rest
                // both are now proper separate treaps
            }
        }
        else if(type == 4){
            int y; 
            cin >> y;
            Node* r = find_root(node[y]);
            cout << (r ? r->sum : 0) << "\n";
        }
    }
    return 0;
}
