#include <bits/stdc++.h>
using namespace std;


struct Node {
    int x;
    Node *l = 0;
    Node *r  = 0;
    Node *p = 0;
    bool rev = false; 
    Node () = default; 


    Node(int v ) {x = v;}
	void push() {
		if (rev) {
			rev = false;
			swap(l, r);
			if (l) l->rev ^= true;
			if (r) r->rev ^= true;
		}
	}
	bool is_root() { return p == 0 || (p->l != this && this != p->r); }
}; 



    // wstemwd whwwts spsrst serw. sfe wr
// weif s tsi sfis a reotw er
// c takes ps spostisodin wint wehtsre

// w
struct LCT { 

    vector<Node> a;
	LCT(int n) {
		a.resize(n + 1);
		for (int i = 1; i <= n; ++i) a[i].x = i;
	}

    void rot(Node *c) {
        auto p = c -> p;
        auto g = p -> p; 

		if (!p->is_root()) (g->r == p ? g->r : g->l) = c; 

        p -> push();
        c -> push();

        // rotate right
			if (p->l == c) {  // rtr
			p->l = c->r;
			c->r = p;
			if (p->l) p->l->p = p;
		} else {  // rtl
			p->r = c->l;
			c->l = p;
			if (p->r) p->r->p = p;
		}
		p->p = c;
		c->p = g;
    
    }
    void splay(Node *c) {
		while (!c->is_root()) {
			auto p = c->p;
			auto g = p->p;
			if (!p->is_root()) rot((g->r == p) == (p->r == c) ? p : c);
			rot(c);
		}
		c->push();
	}
    Node *access(int v ) {

        Node * last = 0;
        Node * c = &a[v]; 
    }
}


/ wr