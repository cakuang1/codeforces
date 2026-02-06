#include <bits/stdc++.h>
using namespace std;

static const long long MOD = 998244353;

struct Fenwick {
    int n;
    vector<long long> bit;
    Fenwick(int n=0): n(n), bit(n+1, 0) {}

    void add(int i, long long v) {
        v %= MOD;
        if (v < 0) v += MOD;
        for (; i <= n; i += i & -i) {
            bit[i] += v;
            if (bit[i] >= MOD) bit[i] -= MOD;
        }
    }

    long long sumPrefix(int i) const {
        long long res = 0;
        for (; i > 0; i -= i & -i) {
            res += bit[i];
            if (res >= MOD) res -= MOD;
        }
        return res;
    }

    long long sumAll() const { return sumPrefix(n); }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<int> P(N);
    for (int i = 0; i < N; i++) cin >> P[i];

    Fenwick bitCnt(N); // counts of seen values, for C(i)
    Fenwick bitDP(N);  // stores dp[v] by value v

    long long ans = 0;

    for (int i = 0; i < N; i++) {
        int x = P[i];

        // sum_v dp[v]
        long long totalDP = bitDP.sumAll();

        // ans += sum_{v > x} dp[v]
        long long dpLeX = bitDP.sumPrefix(x);
        long long suffix = (totalDP - dpLeX) % MOD;
        if (suffix < 0) suffix += MOD;
        ans += suffix;
        ans %= MOD;

        // C(i) = # seen values < x
        long long Ci = bitCnt.sumPrefix(x - 1);

        // dp[x] += C(i) + sum_v dp[v]
        long long addToX = (Ci + totalDP) % MOD;
        bitDP.add(x, addToX);

        // mark x as seen
        bitCnt.add(x, 1);
    }

    cout << ans % MOD << "\n";
    return 0;
}
