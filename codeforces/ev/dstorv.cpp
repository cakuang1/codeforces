#include <bits/stdc++.h>
using namespace std;

static const int MOD = 1000000007;

inline int addmod(int a, int b) {
    int s = a + b;
    if (s >= MOD) s -= MOD;
    return s;
}
inline int mulmod(long long a, long long b) {
    return int((a * b) % MOD);
}
long long modpow(long long a, long long e) {
    long long r = 1 % MOD;
    a %= MOD;
    while (e) {
        if (e & 1) r = (r * a) % MOD;
        a = (a * a) % MOD;
        e >>= 1;
    }
    return r;
}
int invmod(long long x) { return int(modpow((x%MOD+MOD)%MOD, MOD-2)); }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    long long r, h;
    if (!(cin >> N >> r >> h)) return 0;

    string s; 
    cin >> s;

    int A, B;
    cin >> A >> B;

    // Probabilities modulo MOD
    long long rh = (r + h) % MOD;
    int inv_rh = invmod(rh);
    int p = mulmod(r % MOD, inv_rh); // flower disappears probability
    int q = mulmod(h % MOD, inv_rh); // hand disappears probability

    // L[t][j] = l_{t, j}: prefix length t, j incoming hands, end with exactly A hands and 0 flowers
    // R[len][j] = r_{len, j}: suffix length len, j incoming flowers, end with exactly B flowers and 0 hands
    vector<vector<int>> L(N + 1, vector<int>(N + 1, 0));
    vector<vector<int>> R(N + 1, vector<int>(N + 1, 0));

    // Base for L: empty prefix -> probability 1 iff j == A
    for (int j = 0; j <= N; ++j) L[0][j] = (j == A);

    // Build L incrementally: add s[i-1] as the first thing encountered from the right
    for (int i = 1; i <= N; ++i) {
        char c = s[i - 1];
        if (c == 'H') {
            // Adding a hand at the boundary: shift by +1
            // new[t] = old[t+1]
            for (int t = 0; t <= N; ++t) {
                L[i][t] = (t + 1 <= N ? L[i - 1][t + 1] : 0);
            }
        } else { // c == 'R'
            // Flower vs pool of hands:
            // new[t] = p * sum_{s=1..t} q^{t-s} * old[s]
            int S = 0; // running geometric sum with ratio q
            L[i][0] = 0;
            for (int t = 1; t <= N; ++t) {
                S = addmod(mulmod(S, q), L[i - 1][t]);
                L[i][t] = mulmod(p, S);
            }
        }
    }

    // Base for R: empty suffix -> probability 1 iff j == B
    for (int j = 0; j <= N; ++j) R[0][j] = (j == B);

    // Build R incrementally from the right end: len = 1..N, adding s[N-len] at the left boundary
    for (int len = 1; len <= N; ++len) {
        char c = s[N - len];
        if (c == 'R') {
            // Adding a flower at the boundary: shift by +1
            // new[t] = old[t-1]
            R[len][0] = 0;
            for (int t = 1; t <= N; ++t) {
                R[len][t] = R[len - 1][t - 1];
            }
        } else { // c == 'H'
            // Hand vs pool of flowers:
            // new[t] = q * sum_{s=1..t} p^{t-s} * old[s]
            int S = 0; // running geometric sum with ratio p
            R[len][0] = 0;
            for (int t = 1; t <= N; ++t) {
                S = addmod(mulmod(S, p), R[len - 1][t]);
                R[len][t] = mulmod(q, S);
            }
        }
    }

    // iune w
    // redistibuwer
    int ans = 0;
    for (int t = 0; t <= N; ++t) {
        const auto &Lp = L[t];
        const auto &Rs = R[N - t];
        for (int j = 0; j <= N; ++j) {
            ans = addmod(ans, mulmod(Lp[j], Rs[j]));
        }
    }

    cout << ans << '\n';
    return 0;
}


// weal werflwoers inside teh left sdie msut be annchiolabeted werby we wrwetiher a we