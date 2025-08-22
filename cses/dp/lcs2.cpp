#include <bits/stdc++.h>
using namespace std;

static const int MOD = 1e9+7;

// Fenwick (BIT) for range-sum, 1-indexed
struct Fenwick {
    int n;
    vector<int> f;
    Fenwick(int _n): n(_n), f(n+1, 0) {}

    // add v at index i
    void update(int i, int v) {
        for (; i <= n; i += i & -i) {
            f[i] = (f[i] + v) % MOD;
        }
    }

    // sum[1..i]
    int query(int i) const {
        long long s = 0;
        for (; i > 0; i -= i & -i) {
            s += f[i];
        }
        return s % MOD;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> x(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }

    // 1) Coordinate compression
    vector<int> comp = x;
    sort(comp.begin(), comp.end());
    comp.erase(unique(comp.begin(), comp.end()), comp.end());
    int N = comp.size();

    Fenwick ft(N);

    // 2) DP via Fenwick
    for (int i = 0; i < n; i++) {
        int c = int(lower_bound(comp.begin(), comp.end(), x[i]) - comp.begin()) + 1;
        // sum of dp for all values < x[i]
        int s = ft.query(c - 1);
        // dp_i = 1 (the subsequence [x_i] alone) + all extensions
        int dpi = (1 + s) % MOD;
        ft.update(c, dpi);
    }

    // 3) Total number of increasing subsequences = sum of all dp_i
    int answer = ft.query(N);
    cout << answer << "\n";
    return 0;
}
