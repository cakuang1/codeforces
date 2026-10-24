#include <bits/stdc++.h>
using namespace std;

using ll = long long;
constexpr ll INF = (1LL << 60);

struct SegTree {
    int n;
    vector<ll> mn, lazy;

    SegTree(int n) : n(n), mn(4 * n, INF), lazy(4 * n, 0) {}

    void apply(int p, ll x) {
        mn[p] += x;
        lazy[p] += x;
    }

    void push(int p) {
        if (lazy[p] == 0) return;
        apply(p * 2, lazy[p]);
        apply(p * 2 + 1, lazy[p]);
        lazy[p] = 0;
    }

    void setPoint(int p, int l, int r, int pos, ll x) {
        if (l == r) {
            mn[p] = x;
            lazy[p] = 0;
            return;
        }

        push(p);
        int mid = (l + r) / 2;

        if (pos <= mid)
            setPoint(p * 2, l, mid, pos, x);
        else
            setPoint(p * 2 + 1, mid + 1, r, pos, x);

        mn[p] = min(mn[p * 2], mn[p * 2 + 1]);
    }

    void add(int p, int l, int r, int ql, int qr, ll x) {
        if (r < ql || qr < l) return;

        if (ql <= l && r <= qr) {
            apply(p, x);
            return;
        }

        push(p);
        int mid = (l + r) / 2;

        add(p * 2, l, mid, ql, qr, x);
        add(p * 2 + 1, mid + 1, r, ql, qr, x);

        mn[p] = min(mn[p * 2], mn[p * 2 + 1]);
    }

    ll query(int p, int l, int r, int ql, int qr) {
        if (r < ql || qr < l) return INF;
        if (ql <= l && r <= qr) return mn[p];

        push(p);
        int mid = (l + r) / 2;

        return min(
            query(p * 2, l, mid, ql, qr),
            query(p * 2 + 1, mid + 1, r, ql, qr)
        );
    }

    void setPoint(int pos, ll x) {
        setPoint(1, 1, n, pos, x);
    }

    void add(int l, int r, ll x) {
        add(1, 1, n, l, r, x);
    }

    ll query(int l, int r) {
        return query(1, 1, n, l, r);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<ll> A(N + 1);
    for (int i = 1; i <= N; i++) cin >> A[i];

    vector<ll> dp(N + 1, INF);
    dp[0] = 0;

    SegTree seg(N);
    vector<int> maxStack, minStack;

    for (int i = 1; i <= N; i++) {
        // New starting position i: singleton range has score 0.
        seg.setPoint(i, dp[i - 1]);

        // Increasing the maximum increases the candidate cost.
        while (!maxStack.empty() && A[maxStack.back()] <= A[i]) {
            int p = maxStack.back();
            maxStack.pop_back();

            int l = maxStack.empty() ? 1 : maxStack.back() + 1;
            seg.add(l, p, A[i] - A[p]);
        }
        maxStack.push_back(i);

        // Decreasing the minimum also increases the candidate cost.
        while (!minStack.empty() && A[minStack.back()] >= A[i]) {
            int p = minStack.back();
            minStack.pop_back();

            int l = minStack.empty() ? 1 : minStack.back() + 1;
            seg.add(l, p, A[p] - A[i]);
        }
        minStack.push_back(i);

        // Last segment [l, i] must have length at least 2.
        if (i >= 2) {
            dp[i] = seg.query(1, i - 1);
        }
    }

    cout << dp[N] << '\n';
}