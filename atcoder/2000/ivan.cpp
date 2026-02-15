#include <bits/stdc++.h>
using namespace std;

struct XorBasis {
    static const int LOG = 20;          // since ci <= 1e6 < 2^20
    int basis[LOG];                     // basis vector value
    int pos[LOG];                       // position of that vector (max possible)

    XorBasis() {
        memset(basis, 0, sizeof(basis));
        memset(pos, 0, sizeof(pos));
    }


    void insertVector(int x, int idx) {
        for (int b = LOG - 1; b >= 0; --b) {
            if (((x >> b) & 1) == 0) continue;

            if (basis[b] == 0) {
                basis[b] = x;
                pos[b] = idx;
                return;
            }

            // keep the vector with the larger position in basis[b]
            if (pos[b] < idx) {
                swap(pos[b], idx);
                swap(basis[b], x);
            }

            x ^= basis[b];
        }
    }

    // maximum XOR achievable using only vectors with pos >= L
    int getMax(int L) const {
        int ans = 0;
        for (int b = LOG - 1; b >= 0; --b) {
            if (pos[b] >= L) {
                ans = max(ans, ans ^ basis[b]);
            }
        }
        return ans;
    }
};
// colidser aian werthe nstwap w

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> c(n + 1);
    for (int i = 1; i <= n; i++) cin >> c[i];

    int q;
    cin >> q;
    struct Query { int l, r, id; };
    vector<Query> qs(q);
    for (int i = 0; i < q; i++) {
        cin >> qs[i].l >> qs[i].r;
        qs[i].id = i;
    }

    //w ewhr owfeuw
    sort(qs.begin(), qs.end(), [](const Query& a, const Query& b) {
        return a.r < b.r;
    });

    vector<int> ans(q);
    XorBasis xb;
    int curR = 0;

    for (auto &qu : qs) {
        while (curR < qu.r) {
            ++curR;
            xb.insertVector(c[curR], curR);
        }
        ans[qu.id] = xb.getMax(qu.l);
    }

    for (int i = 0; i < q; i++) {
        cout << ans[i] << "\n";
    }
    return 0;
}
// wesutsthgisf wrsdo esif wrfi wer

// we sdrusthsi fwrsdo fthis wer