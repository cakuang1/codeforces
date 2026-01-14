#include <bits/stdc++.h>
using namespace std;

// Treap solution for CF 702F (T-Shirts)
// Idea: process shirts sorted by (quality desc, cost asc).
// Maintain all customers in a treap keyed by remaining money.
// For each shirt cost w:
//   split by w-1: A (can't buy), B (can buy)
//   split B by 2w-1: B1 (w..2w-1), C (>=2w)
//   C: lazy (money -= w, ans += 1) safe (stays >= w)
//   B1: ans += 1, then need to decrease money by w and reinsert individually (money drops below w).
// Amortized: each customer enters B1 only O(log bi) times (money halves).

struct Node {
    int l = 0, r = 0;
    uint32_t pr = 0;
    int sz = 1;

    long long val = 0;   // remaining money (BST key)
    long long add = 0;   // lazy add to val
    int ans = 0;         // shirts bought
    int addAns = 0;      // lazy add to ans

    int id = 0;          // original query index
};

static const int MAXN = 200000 + 5;
Node tr[MAXN];
int tot = 0;

static uint64_t seed64 = chrono::steady_clock::now().time_since_epoch().count();
static inline uint32_t rng32() {
    seed64 += 0x9E3779B97F4A7C15ull;
    uint64_t z = seed64;
    z = (z ^ (z >> 30)) * 0xBF58476D1CE4E5B9ull;
    z = (z ^ (z >> 27)) * 0x94D049BB133111EBull;
    z = z ^ (z >> 31);
    return (uint32_t)z;
}

inline int sz(int p) { return p ? tr[p].sz : 0; }

inline int newNode(long long money, int id) {
    int p = ++tot;
    tr[p] = Node();
    tr[p].pr = rng32();
    tr[p].val = money;
    tr[p].id = id;
    return p;
}

inline void applyVal(int p, long long delta) {
    if (!p) return;
    tr[p].val += delta;
    tr[p].add += delta;
}

inline void applyAns(int p, int delta) {
    if (!p) return;
    tr[p].ans += delta;
    tr[p].addAns += delta;
}

inline void push(int p) {
    if (!p) return;
    if (tr[p].add != 0) {
        applyVal(tr[p].l, tr[p].add);
        applyVal(tr[p].r, tr[p].add);
        tr[p].add = 0;
    }
    if (tr[p].addAns != 0) {
        applyAns(tr[p].l, tr[p].addAns);
        applyAns(tr[p].r, tr[p].addAns);
        tr[p].addAns = 0;
    }
}

inline void pull(int p) {
    if (!p) return;
    tr[p].sz = sz(tr[p].l) + sz(tr[p].r) + 1;
}

// split by key: L has val <= key, R has val > key
void split(int p, long long key, int &L, int &R) {
    if (!p) { L = R = 0; return; }
    push(p);
    if (tr[p].val <= key) {
        L = p;
        split(tr[p].r, key, tr[L].r, R);
        pull(L);
    } else {
        R = p;
        split(tr[p].l, key, L, tr[R].l);
        pull(R);
    }
}

int merge(int L, int R) {
    if (!L || !R) return L ? L : R;
    if (tr[L].pr < tr[R].pr) {
        push(L);
        tr[L].r = merge(tr[L].r, R);
        pull(L);
        return L;
    } else {
        push(R);
        tr[R].l = merge(L, tr[R].l);
        pull(R);
        return R;
    }
}

// collect nodes of a treap in-order into vec (pushes lazies so val is real)
void inorderCollect(int p, vector<int> &vec) {
    if (!p) return;
    push(p);
    inorderCollect(tr[p].l, vec);
    vec.push_back(p);
    inorderCollect(tr[p].r, vec);
}

struct Shirt { long long c, q; };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Shirt> shirts(n);
    for (int i = 0; i < n; i++) cin >> shirts[i].c >> shirts[i].q;

    sort(shirts.begin(), shirts.end(), [](const Shirt& a, const Shirt& b){
        if (a.q != b.q) return a.q > b.q;   // quality desc
        return a.c < b.c;                  // cost asc
    });

    int k;
    cin >> k;
    vector<long long> b(k + 1);
    for (int i = 1; i <= k; i++) cin >> b[i];

    int root = 0;
    for (int i = 1; i <= k; i++) {
        int A, B;
        split(root, b[i], A, B);
        root = merge(A, merge(newNode(b[i], i), B));
    }

    for (auto &sh : shirts) {
        long long w = sh.c;

        int A, B;
        split(root, w - 1, A, B);       // A: < w,  B: >= w
        int B1, C;
        split(B, 2*w - 1, B1, C);       // B1: [w,2w-1], C: >= 2w

        // C: safe lazy update (still >= w after paying)
        applyVal(C, -w);
        applyAns(C, 1);

        // B1: they buy, but fall below w; must reinsert with new key
        applyAns(B1, 1);

        // remove B1 from structure temporarily
        root = merge(A, C);

        vector<int> nodes;
        nodes.reserve(sz(B1));
        inorderCollect(B1, nodes);

        // reinsert each node with updated money
        for (int p : nodes) {
            // p is isolated now (we'll clear links)
            tr[p].val -= w; // no need for applyVal since isolated and pushed
            tr[p].l = tr[p].r = 0;
            tr[p].add = 0;

            int L, R;
            split(root, tr[p].val, L, R);
            root = merge(L, merge(p, R));
        }
    }

    vector<int> nodes;
    nodes.reserve(k);
    inorderCollect(root, nodes);

    vector<int> ans(k + 1, 0);
    for (int p : nodes) ans[tr[p].id] = tr[p].ans;

    for (int i = 1; i <= k; i++) {
        cout << ans[i] << (i == k ? '\n' : ' ');
    }
    return 0;
}


// wewhsdystosh wiwow erk
// wsoktsu arnr sm ewr
./