#include <bits/stdc++.h>
using namespace std;
using ll = long long;
  
struct Node {
    int val;        // your element
    int prio;       // heap priority
    int sz;         // size of subtree
    ll sum;         // subtree sum
    bool rev;       // lazy-reverse flag
    Node *l, *r;
    Node(int _v): val(_v), prio(rand()), sz(1),
                  sum(_v), rev(false), l(nullptr), r(nullptr) {}
};

// helpers for size/sum
int  getSize(Node* t){ return t ? t->sz  : 0; }
ll getSum (Node* t){ return t ? t->sum : 0; }

// push lazy flags down
void push(Node* t){
    if(!t || !t->rev) return;
    t->rev = false;
    swap(t->l, t->r);
    if(t->l) t->l->rev ^= 1;
    if(t->r) t->r->rev ^= 1;
}

// recalc aggregated info
void pull(Node* t){
    if(!t) return;
    t->sz  = 1 + getSize(t->l) + getSize(t->r);
    t->sum = t->val + getSum(t->l) + getSum(t->r);
}

// Split into [0..k-1] and [k..end]
pair<Node*,Node*> split(Node* t, int k){
    if(!t) return {nullptr,nullptr};
    push(t);
    if(getSize(t->l) >= k){
        // split left side
        auto [L,R] = split(t->l, k);
        t->l = R;
        pull(t);
        return {L, t};
    } else {
        // split right side
        auto [L,R] = split(t->r, k - getSize(t->l) - 1);
        t->r = L;
        pull(t);
        return {t, R};
    }
}

// Merge two treaps L and R, with all keys in L before those in R
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

// Insert value v at position pos (0-based)
Node* insert(Node* t, int pos, int v){
    auto [L, R] = split(t, pos);
    Node* node = new Node(v);
    return merge( merge(L, node), R );
}

// Erase element at position pos
Node* erase(Node* t, int pos){
    auto [L, midR] = split(t, pos);
    auto [mid, R]   = split(midR, 1);
    delete mid;
    return merge(L, R);
}

// Reverse the subarray [l..r)
Node* reverseRange(Node* t, int l, int r){
    auto [A, BC] = split(t, l);
    auto [B, C]  = split(BC, r-l);
    if(B) B->rev ^= 1;
    return merge(A, merge(B, C));
}

// Query sum on [l..r)
ll rangeSum(Node* t, int l, int r){
    auto [A, BC] = split(t, l);
    auto [B, C]  = split(BC, r-l);
    ll ans = getSum(B);
    t = merge(A, merge(B, C));
    return ans;
}

// Get element at index pos
int getAt(Node* t, int pos){
    auto [L, midR] = split(t, pos);
    auto [mid, R]  = split(midR, 1);
    int ans = mid->val;
    t = merge(L, merge(mid, R));
    return ans;
}

// Set element at index pos to v
Node* setAt(Node* t, int pos, int v){
    auto [L, midR] = split(t, pos);
    auto [mid, R]  = split(midR, 1);
    mid->val = v;
    pull(mid);
    return merge(L, merge(mid, R));
}

// In-order traversal (for debugging)
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
    Node* treap = nullptr;

    // Example usage:
    // Build from an initial array
    vector<int> a = {5,2,7,3};
    for(int i = 0; i < (int)a.size(); i++){
        treap = insert(treap, i, a[i]);
    }

    cout << "Initial: ";
    inorder(treap); cout<<"\n";

    // Insert 10 at position 2
    treap = insert(treap, 2, 10);
    cout << "After insert 10 at idx 2: ";
    inorder(treap); cout<<"\n";

    // Erase element at pos 3
    treap = erase(treap, 3);
    cout << "After erase at idx 3: ";
    inorder(treap); cout<<"\n";

    // Reverse range [1..4)
    treap = reverseRange(treap, 1, 4);
    cout << "After reverse [1..4): ";
    inorder(treap); cout<<"\n";

    // Range-sum [1..4)
    cout << "Sum [1..4): " << rangeSum(treap, 1, 4) << "\n";

    // Get / set
    cout << "getAt(2): " << getAt(treap,2) << "\n";
    treap = setAt(treap, 2, 42);
    cout << "After setAt(2,42): ";
    inorder(treap); cout<<"\n";

    return 0;
}

