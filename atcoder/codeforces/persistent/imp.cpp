#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val;        // aggregate value on this segment
    Node *l, *r;    // children
    Node(int v = 0, Node* L = nullptr, Node* R = nullptr)
      : val(v), l(L), r(R) {}
};

int N;                   // size of the array (0..N-1)
vector<Node*> roots;     // roots[k] = version after k updates (prefix of length k)

// Build an initial empty tree (all zeros) over [l..r]
Node* build(int l, int r) {
    if (l == r) return new Node(0);
    int m = (l + r) >> 1;
    return new Node(0, build(l, m), build(m+1, r));
}

Node* update(Node* cur, int l, int r, int pos, int delta) {
    if (l == r) {
        // clone and apply delta
        return new Node(cur->val + delta);
    }
    int m = (l + r) >> 1;
    Node *L = cur->l, *R = cur->r;
    if (pos <= m) {
        L = update(cur->l, l, m, pos, delta);
    } else {
        R = update(cur->r, m+1, r, pos, delta);
    }
    return new Node(L->val + R->val, L, R);
}

// Range‑sum query on version `cur` over [ql..qr]
int query(Node* cur, int l, int r, int ql, int qr) {
    if (!cur || qr < l || r < ql) return 0;
    if (ql <= l && r <= qr) return cur->val;
    int m = (l + r) >> 1;
    return query(cur->l, l, m, ql, qr)
         + query(cur->r, m+1, r, ql, qr);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }

    // version 0: empty
    roots.push_back(build(0, N-1));
    // versions 1..N: prefixes of length 1..N
    for (int i = 0; i < N; i++) {
        // insert A[i] at position i
        roots.push_back(update(roots.back(), 0, N-1, i, A[i]));
    }

    // Now roots[k] contains the multiset of A[0..k-1]
    // You can query any version 0 ≤ ver ≤ N

    int Q; 
    cin >> Q;
    while (Q--) {
        int ver, L, R;
        cin >> ver >> L >> R;  
        // ver in [0..N], L,R in [0..N-1]
        cout << query(roots[ver], 0, N-1, L, R) << "\n";
    }

    return 0;
}
