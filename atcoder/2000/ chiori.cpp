#include <bits/stdc++.h>
using namespace std;
static const long long MOD = 998244353;

long long mod_pow(long long a, long long e) {
    long long r = 1 % MOD;
    a %= MOD;
    while (e) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<unsigned long long> basis(m, 0);

    for (int i = 0; i < n; i++) {
        unsigned long long x; cin >> x;
        for (int b = m - 1; b >= 0; --b) {
            if (((x >> b) & 1ULL) == 0) continue;
            if (!basis[b]) { basis[b] = x; break; }
            x ^= basis[b];
        }
    }

    // RREF-like
    for (int i = m - 1; i >= 0; --i) if (basis[i]) {
        for (int j = i - 1; j >= 0; --j)
            if (basis[j] && ((basis[i] >> j) & 1ULL)) basis[i] ^= basis[j];
    }
    for (int i = 0; i < m; ++i) if (basis[i]) {
        for (int j = 0; j < m; ++j)
            if (j != i && basis[j] && ((basis[j] >> i) & 1ULL)) basis[j] ^= basis[i];
    }

    vector<unsigned long long> vecs;
    vector<char> is_pivot(m, 0);
    for (int i = 0; i < m; ++i) if (basis[i]) {
        vecs.push_back(basis[i]);
        is_pivot[i] = 1;
    }
    int k = (int)vecs.size();
    int d = m - k;

    vector<long long> pcount(m + 1, 0);

    // Branch correctly to avoid 2^d explosion/overflow
    if (k <= 20) {
        // Enumerate all 2^k codewords directly
        int S = 1 << k;
        unsigned long long cur = 0;
        pcount[0] = 1;
        for (int mask = 1; mask < S; ++mask) {
            int lb = __builtin_ctz(mask);
            cur ^= vecs[lb];
            pcount[__builtin_popcountll(cur)]++;
        }
        for (int w = 0; w <= m; ++w) pcount[w] %= MOD;
    } else {
        // Your DP over free bits (now d is small)
        vector<int> freePos;
        for (int i = 0; i < m; ++i) if (!is_pivot[i]) freePos.push_back(i);
        // d should be <= 15-ish here for E1 typical; but anyway safe because k>20 implies d < 15 when m<=35.
        int S = 1 << d;

        vector<int> projMask(k, 0);
        for (int i = 0; i < k; ++i) {
            unsigned long long v = vecs[i];
            int mask = 0;
            for (int t = 0; t < d; ++t)
                if ((v >> freePos[t]) & 1ULL) mask |= (1 << t);
            projMask[i] = mask;
        }

        vector<vector<long long>> dp(k + 1, vector<long long>(S, 0));
        dp[0][0] = 1;
        for (int i = 0; i < k; ++i) {
            int mv = projMask[i];
            for (int j = i; j >= 0; --j) {
                for (int s = 0; s < S; ++s) {
                    long long val = dp[j][s];
                    if (!val) continue;
                    int ns = s ^ mv;
                    dp[j + 1][ns] += val;
                    if (dp[j + 1][ns] >= MOD) dp[j + 1][ns] -= MOD;
                }
            }
        }

        for (int j = 0; j <= k; ++j) {
            for (int s = 0; s < S; ++s) if (dp[j][s]) {
                int w = j + __builtin_popcount((unsigned)s);
                pcount[w] = (pcount[w] + dp[j][s]) % MOD;
            }
        }
    }

    / /wetugs sdtf r nsirah 
    // wes s exca ets darsvwer

    long long mult = mod_pow(2, n - k);
    for (int w = 0; w <= m; ++w) {
        cout << (pcount[w] * mult % MOD) << (w == m ? '\n' : ' ');
    }
    return 0;
}



// w wrsnusmers oftsof spi weshowshiso wr
// wrhdoous jweri wer