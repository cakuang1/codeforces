#include <bits/stdc++.h>
using namespace std;

using int64 = long long;
using i128 = __int128_t;

// Fast power (a^e mod m)
static inline int64 modpow(int64 a, int64 e, int64 m) {
    int64 r = 1 % m;
    a %= m;
    while (e > 0) {
        if (e & 1) r = (i128)r * a % m;
        a = (i128)a * a % m;
        e >>= 1;
    }
    return r;
}

// Extended GCD: returns g = gcd(a,b), and finds x,y with ax + by = g
static inline int64 extgcd(int64 a, int64 b, int64 &x, int64 &y) {
    if (b == 0) { x = (a >= 0 ? 1 : -1); y = 0; return llabs(a); }
    int64 x1, y1;
    int64 g = extgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

// Modular inverse of a modulo m (assumes gcd(a,m)=1)
static inline int64 modinv(int64 a, int64 m) {
    int64 x, y;
    int64 g = extgcd(a, m, x, y);
    // assuming gcd(a,m)=1
    x %= m;
    if (x < 0) x += m;
    return x;
}

// We’ll precompute factorials and inverse factorials modulo each small prime p (<50).
struct FactTable {
    vector<int64> fact, invfact;
};

static map<int,int> prime_index;         // prime -> index in tables
static vector<int> used_primes;          // list of primes actually used
static vector<FactTable> tables;         // precomputed per-prime tables

// Build factorials mod p
void ensure_prime_precomputed(int p) {
    if (prime_index.count(p)) return;
    prime_index[p] = (int)used_primes.size();
    used_primes.push_back(p);
    FactTable ft;
    ft.fact.resize(p);
    ft.invfact.resize(p);
    ft.fact[0] = 1;
    for (int i = 1; i < p; ++i) ft.fact[i] = (ft.fact[i-1] * i) % p;
    // Use Fermat for inverses since p is prime
    for (int i = 0; i < p; ++i) {
        ft.invfact[i] = modpow(ft.fact[i], p - 2, p);
    }
    tables.push_back(move(ft));
}

// nCk mod prime p, with n,k < p (small)
static inline int64 nCk_small_mod_p(int n, int k, int p) {
    if (k < 0 || k > n) return 0;
    int idx = prime_index[p];
    const auto &ft = tables[idx];
    int64 res = ft.fact[n];
    res = (res * ft.invfact[k]) % p;
    res = (res * ft.invfact[n - k]) % p;
    return res;
}

// Lucas theorem: C(n, k) mod prime p
int64 nCk_lucas_mod_p(int64 n, int64 k, int p) {
    if (k < 0 || k > n) return 0;
    ensure_prime_precomputed(p);
    int64 res = 1;
    while (n > 0 || k > 0) {
        int ni = (int)(n % p);
        int ki = (int)(k % p);
        if (ki > ni) return 0;
        res = (res * nCk_small_mod_p(ni, ki, p)) % p;
        n /= p;
        k /= p;
    }
    return res;
}

// Factor M into distinct primes (<50). M is square-free by problem statement.
vector<int> factor_squarefree_primes(int64 M) {
    static const int small_primes[] = {
        2,3,5,7,11,13,17,19,23,29,31,37,41,43,47
    };
    vector<int> ps;
    for (int p : small_primes) {
        if (M % p == 0) {
            ps.push_back(p);
            M /= p;
        }
    }
    // If constraints hold, M should now be 1.
    // But in case an unexpected leftover prime > 50 appears (shouldn't), we handle it:
    if (M > 1) {
        // Treat leftover as a prime (this would break assumptions if >= 50).
        // We still attempt; building factorial table of size M is impossible for big M.
        // The problem guarantees primes < 50, so this path should not happen.
        ps.push_back((int)M);
    }
    return ps;
}

// CRT for pairwise coprime moduli (here primes). Returns in [0, mod-1].
int64 crt_combine(const vector<int64> &rem, const vector<int64> &mod) {
    int64 M = 1;
    int n = (int)mod.size();
    for (int i = 0; i < n; ++i) M *= mod[i];
    i128 x = 0;
    for (int i = 0; i < n; ++i) {
        int64 mi = mod[i];
        int64 Mi = M / mi;
        // inverse of Mi modulo mi
        int64 inv = modinv(Mi % mi, mi);
        i128 term = (i128)rem[i] * Mi % M;
        term = term * inv % M;
        x = (x + term) % M;
    }
    int64 ans = (int64)(x % M);
    if (ans < 0) ans += M;
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int64 N, R, M;
        cin >> N >> R >> M;

        if (M == 1) { // everything mod 1 is 0
            cout << 0 << "\n";
            continue;
        }
        if (R < 0 || R > N) {
            cout << 0 << "\n";
            continue;
        }

        // factor M into distinct primes (<50)
        vector<int> primes = factor_squarefree_primes(M);

        // Compute C(N, R) mod each prime
        vector<int64> residues, moduli;
        residues.reserve(primes.size());
        moduli.reserve(primes.size());
        bool failed = false;

        for (int p : primes) {
            if (p <= 1) { failed = true; break; }
            if (p >= 50) {
                // According to constraints this should not happen; guard anyway.
                // We cannot precompute factorials up to p if p is large here.
                // Mark as failed; still, the test data should never trigger this.
                failed = true;
                break;
            }
            int64 r = nCk_lucas_mod_p(N, R, p);
            residues.push_back(r);
            moduli.push_back(p);
        }

        if (failed) {
            // Defensive: if constraints were violated, we can’t compute reliably.
            // But per problem, this should never print.
            cout << 0 << "\n";
            continue;
        }

        // Combine via CRT since moduli are pairwise coprime (square-free)
        int64 ans = crt_combine(residues, moduli);
        // Ensure answer is modulo original M (product of primes)
        // In case factorization introduced a leftover, rebuild M from moduli:
        int64 M2 = 1;
        for (auto v : moduli) M2 *= v;
        if (M2 != M) {
            // If this ever differs (shouldn't), reduce to original M anyway
            ans %= M;
        }
        cout << ans % M << "\n";
    }
    return 0;
}

//