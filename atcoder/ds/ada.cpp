#include <bits/stdc++.h>
using namespace std;

struct item {
    int prior;
    int cnt;
    int value;

    long long sum;
    int mn, mx;

    long long add;   // lazy range add
    bool rev;        // lazy reverse

    item *l, *r;

    item(int v) : prior(rand()), cnt(1), value(v),
                  sum(v), mn(v), mx(v),
                  add(0), rev(false), l(nullptr), r(nullptr) {}
};

using pitem = item*;

/* ---------- basic getters ---------- */

int cnt(pitem t) { return t ? t->cnt : 0; }
long long sum(pitem t) { return t ? t->sum : 0; }
int mn(pitem t) { return t ? t->mn : INT_MAX; }
int mx(pitem t) { return t ? t->mx : INT_MIN; }

/* ---------- recompute ---------- */

void upd(pitem t) {
    if (!t) return;
    t->cnt = 1 + cnt(t->l) + cnt(t->r);
    t->sum = t->value + sum(t->l) + sum(t->r);
    t->mn = min(t->value, min(mn(t->l), mn(t->r)));
    t->mx = max(t->value, max(mx(t->l), mx(t->r)));
}

/* ---------- lazy helpers ---------- */

void apply_add(pitem t, long long v) {
    if (!t) return;
    t->value += v;
    t->sum += v * t->cnt;
    t->mn += v;
    t->mx += v;
    t->add += v;
}

void push(pitem t) {
    if (!t) return;

    // reverse
    if (t->rev) {
        t->rev = false;
        swap(t->l, t->r);
        if (t->l) t->l->rev ^= 1;
        if (t->r) t->r->rev ^= 1;
    }

    // add
    if (t->add != 0) {
        apply_add(t->l, t->add);
        apply_add(t->r, t->add);
        t->add = 0;
    }
}

/* ---------- merge & split ---------- */

void merge(pitem &t, pitem l, pitem r) {
    push(l);
    push(r);
    if (!l || !r) {
        t = l ? l : r;
    } else if (l->prior > r->prior) {
        merge(l->r, l->r, r);
        t = l;
    } else {
        merge(r->l, l, r->l);
        t = r;
    }
    upd(t);
}

void split(pitem t, pitem &l, pitem &r, int key, int add = 0) {
    if (!t) {
        l = r = nullptr;
        return;
    }
    push(t);

    int cur = add + cnt(t->l);
    if (key <= cur) {
        split(t->l, l, t->l, key, add);
        r = t;
    } else {
        split(t->r, t->r, r, key, add + 1 + cnt(t->l));
        l = t;
    }
    upd(t);
}

/* ---------- operations ---------- */

// insert value v at position pos
void insert(pitem &t, int pos, int v) {
    pitem a, b;
    split(t, a, b, pos);
    merge(a, a, new item(v));
    merge(t, a, b);
}

// erase element at position pos
void erase(pitem &t, int pos) {
    pitem a, b, c;
    split(t, a, b, pos);
    split(b, b, c, 1);
    // delete b; // optional
    merge(t, a, c);
}

// reverse range [l, r]
void range_reverse(pitem &t, int l, int r) {
    pitem a, b, c;
    split(t, a, b, l);
    split(b, b, c, r - l + 1);
    if (b) b->rev ^= 1;
    merge(t, a, b);
    merge(t, t, c);
}

// add v to range [l, r]
void range_add(pitem &t, int l, int r, long long v) {
    pitem a, b, c;
    split(t, a, b, l);
    split(b, b, c, r - l + 1);
    apply_add(b, v);
    merge(t, a, b);
    merge(t, t, c);
}

long long range_sum(pitem &t, int l, int r) {
    pitem a, b, c;
    split(t, a, b, l);
    split(b, b, c, r - l + 1);
    long long res = sum(b);
    merge(t, a, b);
    merge(t, t, c);
    return res;
}

int range_min(pitem &t, int l, int r) {
    pitem a, b, c;
    split(t, a, b, l);
    split(b, b, c, r - l + 1);
    int res = mn(b);
    merge(t, a, b);
    merge(t, t, c);
    return res;
}

int range_max(pitem &t, int l, int r) {
    pitem a, b, c;
    split(t, a, b, l);
    split(b, b, c, r - l + 1);
    int res = mx(b);
    merge(t, a, b);
    merge(t, t, c);
    return res;
}

/* ---------- traversal ---------- */

void output(pitem t) {
    if (!t) return;
    push(t);
    output(t->l);
    cout << t->value << ' ';
    output(t->r);
}




int q;
    cin >> q;
    pitem t;
    int l = 0; 


    // merge with new node wer
    for (int i = 0 ; i < q ; i ++ ) {
        int a,v; cin >> a >> v;
        int first = a ^ l;
        int rand =  v ^ l;
        // Wh sydstshf owsdifh wirwk wr 
        . we
    }
}