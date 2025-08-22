#include <bits/stdc++.h>
using namespace std;

struct SegTree {
    int n;
    vector<int> st;
    SegTree(int _n): n(_n), st(4*_n+4, 0) {}

    int query(int p, int l, int r, int i, int j) {
        if (r < i || l > j) return 0;
        if (l >= i && r <= j) return st[p];
        int m = (l + r) >> 1;
        return max(
            query(p<<1,     l,   m, i, j),
            query(p<<1|1, m+1,   r, i, j)
        );
    }
    int query(int l, int r) {
        if (l > r) return 0;
        return query(1, 1, n, l, r);
    }

    void update(int p, int l, int r, int idx, int val) {
        if (l == r) {
            st[p] = val;
            return;
        }
        int m = (l + r) >> 1;
        if (idx <= m) update(p<<1, l, m, idx, val);
        else          update(p<<1|1, m+1, r, idx, val);
        st[p] = max(st[p<<1], st[p<<1|1]);
    }
    void update(int idx, int val) {
        update(1, 1, n, idx, val);
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> h(n+1);
    for(int i = 1; i <= n; i++){
        cin >> h[i];
    }

    // Nearest greater to left (L) and right (R)
    vector<int> L(n+1), R(n+1);
    stack<int> st;
    // compute L[i]
    for(int i = 1; i <= n; i++){
        while(!st.empty() && h[st.top()] <= h[i]) st.pop();
        L[i] = st.empty() ? 0 : st.top();
        st.push(i);
    }
    // clear and compute R[i]
    while(!st.empty()) st.pop();
    for(int i = n; i >= 1; i--){
        while(!st.empty() && h[st.top()] <= h[i]) st.pop();
        R[i] = st.empty() ? n+1 : st.top();
        st.push(i);
    }

    // Prepare order of processing by increasing height
    vector<pair<int,int>> order;
    order.reserve(n);
    for(int i = 1; i <= n; i++){
        order.emplace_back(h[i], i);
    }
    sort(order.begin(), order.end());

    SegTree seg(n);
    vector<int> dp(n+1, 0);
    int ans = 0;

    // Process in groups of equal height
    for(int i = 0; i < n; ){
        int j = i;
        while(j < n && order[j].first == order[i].first) j++;

        // Compute dp for this group (using only values from strictly smaller heights)
        for(int k = i; k < j; k++){
            int idx = order[k].second;
            int l = L[idx] + 1;
            int r = R[idx] - 1;
            dp[idx] = 1 + seg.query(l, r);
        }
        // Update segment tree for this group
        for(int k = i; k < j; k++){
            int idx = order[k].second;
            seg.update(idx, dp[idx]);
            ans = max(ans, dp[idx]);
        }

        i = j;
    }

    cout << ans << "\n";
    return 0;
}
