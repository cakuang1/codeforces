#include <bits/stdc++.h>
using namespace std;

// Treap node
struct Node {
    int val, prio, sz;
    bool rev;
    Node *l, *r, *p;
    Node(int v): val(v), prio(rand()), sz(1), rev(false),
                 l(nullptr), r(nullptr), p(nullptr) {}
};

// Push down a reversal flag
void push(Node* t) {
    if (!t || !t->rev) return;
    t->rev = false;
    swap(t->l, t->r);
    if (t->l) t->l->rev ^= 1;
    if (t->r) t->r->rev ^= 1;
}

// Recompute subtree size and fix parent pointers
void pull(Node* t) {
    if (!t) return;
    t->sz = 1;
    if (t->l)  { t->sz += t->l->sz;  t->l->p = t; }
    if (t->r)  { t->sz += t->r->sz;  t->r->p = t; }
}

// Split `t` into [0..k-1] and [k..end], by index
pair<Node*,Node*> split(Node* t, int k) {
    if (!t) return {nullptr,nullptr};
    push(t);
    int lsz = t->l ? t->l->sz : 0;
    if (k <= lsz) {
        auto p = split(t->l, k);
        t->l = p.second;
        pull(t);
        if (p.second) p.second->p = t;
        return {p.first, t};
    } else {
        auto p = split(t->r, k - lsz - 1);
        t->r = p.first;
        pull(t);
        if (p.first) p.first->p = t;
        return {t, p.second};
    }
}

// Merge two treaps a (all indices < b) and b
Node* merge(Node* a, Node* b) {
    if (!a || !b) return a ? a : b;
    if (a->prio < b->prio) {
        push(a);
        a->r = merge(a->r, b);
        pull(a);
        return a;
    } else {
        push(b);
        b->l = merge(a, b->l);
        pull(b);
        return b;
    }
}

// Return 0-based index of node t in its treap
int indexOf(Node* t) {
    vector<Node*> stk;
    for (Node* v = t; v; v = v->p) stk.push_back(v);
    // push down all reversals on the path
    for (int i = stk.size()-1; i >= 0; i--) push(stk[i]);
    int idx = t->l ? t->l->sz : 0;
    while (t->p) {
        if (t == t->p->r) {
            idx += 1 + (t->p->l ? t->p->l->sz : 0);
        }
        t = t->p;
    }
    return idx;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    srand(0xC0FFEE);

    int n;
    cin >> n;
    vector<int>a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    // Build treap and store pointers
    Node* root = nullptr;
    vector<Node*> where(n+1,nullptr);
    for (int i = 0; i < n; i++) {
        Node* nd = new Node(a[i]);
        where[a[i]] = nd;
        root = merge(root, nd);
    }

    vector<pair<int,int>> ops;
    ops.reserve(n);

    // For each target value i=1..n
    for (int i = 1; i <= n; i++) {
        Node* nd = where[i];
        int pos = indexOf(nd); // 0-based
        if (pos != i-1) {
            // we need to reverse [i-1, pos]
            auto p1 = split(root, i-1);
            auto p2 = split(p1.second, pos-(i-1)+1);
            // p2.first is the segment to reverse
            p2.first->rev ^= 1;
            root = merge(p1.first, merge(p2.first, p2.second));
            ops.emplace_back(i, pos+1); // record 1-based
        }
    }

    cout << ops.size() << "\n";
    for (auto &pr : ops) {
        cout << pr.first << " " << pr.second << "\n";
    }
    return 0;
}
