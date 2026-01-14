#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e6 + 10;
int n;
ll s;
ll dp[N];

struct Building {
    ll c, v;
    bool operator<(const Building &rhs) const {
        if (c != rhs.c) return c < rhs.c;
        return v < rhs.v;
    }
} a[N];

// intersection x-coordinate between lines from i and j
// slope2 is a helper for integer division with ceiling
ll slope2(int i, int j) {
    return (a[j].v - a[i].v - 1 + dp[i] - dp[j]) / (a[j].v - a[i].v);
}

bool chk(int i, int j, int k) {
    return slope2(i, j) >= slope2(j, k);
}

// slope of line through i and j
ll slope(int i, int j) {
    return (dp[i] - dp[j]) / (a[j].v - a[i].v);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> s;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].v >> a[i].c;
    }
    sort(a + 1, a + 1 + n);

    // initialize dp to large value
    for (int i = 0; i <= n; i++) dp[i] = (ll)4e18;

    deque<int> q;
    ll ans = (ll)4e18;

    for (int i = 1; i <= n; i++) {
        // prune dominated buildings
        if (!q.empty() && a[q.back()].v >= a[i].v) continue;

        // find best previous
        while (q.size() > 1 &&
               slope(q[0], q[1]) * a[q[0]].v + dp[q[0]] < a[i].c) {
            q.pop_front();
        }

        if (i == 1) {
            dp[i] = 0;
        } else if (!q.empty()) {
            ll t = (a[i].c - dp[q[0]] + a[q[0]].v - 1) / a[q[0]].v;
            ll rem = t * a[q[0]].v + dp[q[0]] - a[i].c;
            dp[i] = rem - t * a[i].v;
        } else {
            continue;
        }

        // update answer: finish using building i
        ans = min(ans, (s - dp[i] + a[i].v - 1) / a[i].v);

        // maintain hull
        while (q.size() > 1 && chk(q[q.size() - 2], q.back(), i)) {
            q.pop_back();
        }
        q.push_back(i);
    }

    cout << ans << "\n";
    return 0;
}

// 
