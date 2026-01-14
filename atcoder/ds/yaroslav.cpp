#include <bits/stdc++.h>
using namespace std;

struct Query {
    int t;
    int p;
    long long d;
    long long l, r;
};

struct Node {
    long long cnt = 0;   // #active points
    long long sum = 0;   // sum of coordinates
    long long ans = 0;   // sum of pairwise distances within segment
};

static inline Node mergeNode(const Node& A, const Node& B) {
    Node C;
    C.cnt = A.cnt + B.cnt;
    C.sum = A.sum + B.sum;
    // cross = sum_{a in A, b in B} (b - a)  with all coords in A <= all coords in B
    long long cross = A.cnt * B.sum - B.cnt * A.sum;
    C.ans = A.ans + B.ans + cross;
    return C;
}

struct SegTree {
    int n; // power of two
    vector<Node> st;
    vector<long long> coord;

    SegTree(const vector<long long>& coords) : coord(coords) {
        int m = (int)coord.size();
        n = 1;
        while (n < m) n <<= 1;
        st.assign(2 * n, Node());
    }

    void setActive(int idx, bool active) {
        int i = idx + n;
        if (active) {
            st[i].cnt = 1;
            st[i].sum = coord[idx];
            st[i].ans = 0;
        } else {
            st[i] = Node();
        }
        for (i >>= 1; i >= 1; i >>= 1) {
            st[i] = mergeNode(st[i << 1], st[i << 1 | 1]);
        }
    }

    Node query(int l, int r) { // inclusive
        if (l > r) return Node();
        Node leftAcc, rightAcc;
        int L = l + n, R = r + n;
        while (L <= R) {
            if (L & 1) leftAcc = mergeNode(leftAcc, st[L++]);
            if (!(R & 1)) rightAcc = mergeNode(st[R--], rightAcc);
            L >>= 1; R >>= 1;
        }
        return mergeNode(leftAcc, rightAcc);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<long long> x(n + 1);
    for (int i = 1; i <= n; i++) cin >> x[i];

    int m;
    cin >> m;
    vector<Query> qs(m);

    // Offline: collect all coordinates that will ever appear
    vector<long long> all;
    all.reserve(n + m);
    for (int i = 1; i <= n; i++) all.push_back(x[i]);

    vector<long long> cur = x;
    for (int i = 0; i < m; i++) {
        int t;
        cin >> t;
        qs[i].t = t;
        if (t == 1) {
            int p; long long d;
            cin >> p >> d;
            qs[i].p = p;
            qs[i].d = d;
            cur[p] += d;
            all.push_back(cur[p]);
        } else {
            long long l, r;
            cin >> l >> r;
            qs[i].l = l;
            qs[i].r = r;
        }
    }

    sort(all.begin(), all.end());
    all.erase(unique(all.begin(), all.end()), all.end());

    auto getIdx = [&](long long val) -> int {
        return (int)(lower_bound(all.begin(), all.end(), val) - all.begin());
    };

    SegTree st(all);

    // initial positions
    vector<int> pos(n + 1);
    for (int i = 1; i <= n; i++) {
        pos[i] = getIdx(x[i]);
        st.setActive(pos[i], true);
    }

    for (int i = 0; i < m; i++) {
        if (qs[i].t == 1) {
            int p = qs[i].p;
            long long d = qs[i].d;

            st.setActive(pos[p], false);
            x[p] += d;
            pos[p] = getIdx(x[p]);
            st.setActive(pos[p], true);
        } else {
            long long l = qs[i].l, r = qs[i].r;
            int L = (int)(lower_bound(all.begin(), all.end(), l) - all.begin());
            int R = (int)(upper_bound(all.begin(), all.end(), r) - all.begin()) - 1;
            if (L > R) cout << 0 << "\n";
            else cout << st.query(L, R).ans << "\n";
        }
    }
    return 0;
}
// wewtof wrof whweigieh wrnw W
// wwnwa wec ero ewrparmsovsf axchjo rarmeosvsigngs twows
//w sf hwow ermakrsns r
// eesrustshi wfsdowisnf owirhsodfosutsdf ioahrosfn sogusf shrsohf sirw
// werds omain soirsarangsf srmns w
//w ed ostsif wowwkr