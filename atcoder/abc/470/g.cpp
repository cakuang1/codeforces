#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct SegTree {
    int n;
    vector<ll> sum;
    vector<int> mx, lazy;

    SegTree(const vector<int>& a) {
        n = (int)a.size() - 1;
        sum.resize(4 * n);
        mx.resize(4 * n);
        lazy.assign(4 * n, -1);
        build(1, 1, n, a);
    }

    void pull(int v) {
        sum[v] = sum[v * 2] + sum[v * 2 + 1];
        mx[v] = max(mx[v * 2], mx[v * 2 + 1]);
    }

    void apply(int v, int l, int r, int value) {
        sum[v] = 1LL * (r - l + 1) * value;
        mx[v] = value;
        lazy[v] = value;
    }

    void push(int v, int l, int r) {
        if (lazy[v] == -1 || l == r) return;

        int mid = (l + r) / 2;
        apply(v * 2, l, mid, lazy[v]);
        apply(v * 2 + 1, mid + 1, r, lazy[v]);
        lazy[v] = -1;
    }

    void build(int v, int l, int r, const vector<int>& a) {
        if (l == r) {
            sum[v] = mx[v] = a[l];
            return;
        }

        int mid = (l + r) / 2;
        build(v * 2, l, mid, a);
        build(v * 2 + 1, mid + 1, r, a);
        pull(v);
    }

    void assignRange(int v, int l, int r,
                     int ql, int qr, int value) {
        if (qr < l || r < ql) return;

        if (ql <= l && r <= qr) {
            apply(v, l, r, value);
            return;
        }

        push(v, l, r);
        int mid = (l + r) / 2;

        assignRange(v * 2, l, mid, ql, qr, value);
        assignRange(v * 2 + 1, mid + 1, r, ql, qr, value);
        pull(v);
    }

    ll querySum(int v, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return 0;
        if (ql <= l && r <= qr) return sum[v];

        push(v, l, r);
        int mid = (l + r) / 2;

        return querySum(v * 2, l, mid, ql, qr)
             + querySum(v * 2 + 1, mid + 1, r, ql, qr);
    }

    // Find the first index in [ql, qr] whose value exceeds x.
    int firstGreater(int v, int l, int r,
                     int ql, int qr, int x) {
        if (qr < l || r < ql || mx[v] <= x) return -1;
        if (l == r) return l;

        push(v, l, r);
        int mid = (l + r) / 2;

        int result = firstGreater(v * 2, l, mid, ql, qr, x);
        if (result != -1) return result;

        return firstGreater(v * 2 + 1, mid + 1, r, ql, qr, x);
    }

    void assignRange(int l, int r, int value) {
        if (l <= r) assignRange(1, 1, n, l, r, value);
    }

    ll querySum(int l, int r) {
        return querySum(1, 1, n, l, r);
    }

    int firstGreater(int l, int r, int x) {
        if (l > r) return -1;
        return firstGreater(1, 1, n, l, r, x);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> A(N + 1);
    for (int i = 1; i <= N; ++i) cin >> A[i];

    // Initial F[r] = mex(A[1 ... r]).
    vector<int> F(N + 1);
    vector<bool> seen(N + 2, false);

    int mex = 0;
    for (int r = 1; r <= N; ++r) {
        seen[A[r]] = true;
        while (seen[mex]) ++mex;
        F[r] = mex;
    }

    // Next occurrence of the same value.
    vector<int> nextPos(N + 1);
    vector<int> last(N + 1, N + 1);

    for (int i = N; i >= 1; --i) {
        nextPos[i] = last[A[i]];
        last[A[i]] = i;
    }
    SegTree seg(F);
    ll answer = 0;

    for (int l = 1; l <= N; ++l) {
        // Currently F[r] = mex(A[l ... r]) for r >= l.
        answer += seg.querySum(l, N);

        // Remove A[l] to prepare for left endpoint l+1.
        int x = A[l];
        int right = nextPos[l] - 1;

        int q = seg.firstGreater(l + 1, right, x);

        if (q != -1) {
            seg.assignRange(q, right, x);
        }
    }

    cout << answer << '\n';
    return 0;
}