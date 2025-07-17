#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Node {
    int val, prio, sz;
    ll sum;
    bool rev;
    Node *l, *r;
    Node(int _v)
      : val(_v), prio(rand()), sz(1),
        sum(_v), rev(false), l(nullptr), r(nullptr)
    {}
};

int  getSize(Node* t){ return t ? t->sz  : 0; }
ll getSum (Node* t){ return t ? t->sum : 0; }

void push(Node* t){
    if(!t || !t->rev) return;
    t->rev = false;
    swap(t->l, t->r);
    if(t->l) t->l->rev ^= 1;
    if(t->r) t->r->rev ^= 1;
}



void pull(Node* t){
    if(!t) return;
    t->sz  = 1 + getSize(t->l) + getSize(t->r);
    t->sum = t->val + getSum(t->l) + getSum(t->r);
} 


pair<Node*,Node*> split(Node* t, int k){
    if(!t) return {nullptr,nullptr};
    push(t);
    if(getSize(t->l) >= k){
        auto [L,R] = split(t->l, k);
        t->l = R;
        pull(t);
        return {L, t};
    } else {
        auto [L,R] = split(t->r, k - getSize(t->l) - 1);
        t->r = L;
        pull(t);
        return {t, R};
    }
}   


Node* merge(Node* L, Node* R){
    if(!L) return R;
    if(!R) return L;
    if(L->prio < R->prio){
        push(L);
        L->r = merge(L->r, R);
        pull(L);
        return L;
    } else {
        push(R);
        R->l = merge(L, R->l);
        pull(R);
        return R;
    }
}

Node* insert(Node* t, int pos, int v){
    auto [A,B] = split(t, pos);
    Node* nd = new Node(v);
    return merge( merge(A, nd), B );
}

void inorder(Node* t){
    if(!t) return;
    push(t);
    inorder(t->l);
    cout << t->val << ' ';
    inorder(t->r);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    srand(time(nullptr));

    int n;
    cin >> n;
    Node* treap = nullptr;

    // build initial sequence 1,2,...,n
    for(int i = 0; i < n; i++){
        treap = insert(treap, i, i+1);
    }

    // process n pairs (a,b)
    for(int i = 0; i < n; i++){
        int a, b;
        cin >> a >> b;
        // convert to 0-based
        --a; 
        --b;
        if(b <= a) continue;
        int dist = min(b - a - 1, (n - 1) - b);
        int len  = dist + 1;
                     
        // split into A | B | C | D | E
        // A = [0..a-1]
        auto [A, BCDE] = split(treap, a);
        // B = [a..a+len-1]
        auto [B, CDE]  = split(BCDE, len);
        // C = [a+len..b-1], length = b - (a+len)
        int gap = b - (a + len);
        auto [C, DE]   = split(CDE, gap);
        // D = [b..b+len-1]
        auto [D, E]    = split(DE, len);

        // reassemble A | D | C | B | E
        treap = merge(
                    A,
                    merge(
                      D,
                      merge(
                        C,
                        merge(B, E)
                      )
                    )
                 );
    }

    // output final sequence
    inorder(treap);
    cout << "\n";
    return 0;
}


//