#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// ---------- extended gcd & linear congruence ----------

static ll extgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) { x = (a >= 0 ? 1 : -1); y = 0; return llabs(a); }
    ll x1, y1;
    ll g = extgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

// solve a*x ≡ b (mod m). Returns (has_solution, x0, step), where all solutions are x = x0 + t*step, step = m/g.
static tuple<bool, ll, ll> solve_lincong(ll a, ll b, ll m) {
    // normalize to [0, m)
    auto modnorm = [&](ll v, ll mod)->ll{
        v %= mod; if (v < 0) v += mod; return v;
    };
    a = modnorm(a, m);
    b = modnorm(b, m);

    ll x, y;
    ll g = extgcd(a, m, x, y);
    if (b % g != 0) return {false, 0, 0};

    ll m2 = m / g;
    // x is inverse of a/g modulo m/g, up to sign.
    // Particular solution: x0 = (b/g) * (x mod m/g) mod m/g
    ll inv = x % m2; if (inv < 0) inv += m2;
    __int128 t = (__int128)(b / g) * inv % m2;
    ll x0 = (ll)t;
    return {true, x0, m2};
}

// ceil division for (a + b - 1) / b, handling negatives safely
static inline ll ceil_div(ll a, ll b) {
    if (b < 0) a = -a, b = -b;
    if (a >= 0) return (a + b - 1) / b;
    // a < 0
    return a / b;
}

// ---------- helpers ----------

static inline int num_digits_ll(ll k) {
    // k >= 1
    int d = 0;
    while (k) { ++d; k /= 10; }
    return d;
}

// pow10 values up to 10^10 fit in 64-bit
static inline ll pow10_int(int e) {
    static ll p10[20] = {0};
    static bool init = false;
    if (!init) {
        init = true;
        p10[0] = 1;
        for (int i = 1; i < 20; ++i) p10[i] = p10[i-1] * 10LL;
    }
    return p10[e];
}

// build string of exactly q digits from x with leading zeros
static string zpad(ll x, int q) {
    string t(q, '0');
    for (int i = q-1; i >= 0; --i) {
        t[i] = char('0' + (x % 10));
        x /= 10;
    }
    return t;
}

// 
void solve() {
    ll K;
    string S;
    cin >> K >> S;

    // d = number of digits of K
    int d = num_digits_ll(K);

    // Precompute 10^e mod K up to |S| + d
    int maxE = (int)S.size() + d;
    vector<ll> pow10mod(maxE + 1);
    pow10mod[0] = 1 % K;
    for (int i = 1; i <= maxE; ++i) pow10mod[i] = (__int128)pow10mod[i-1] * 10 % K;

    // S % K
    ll Smod = 0;
    for (char c : S) {
        Smod = ( (__int128)Smod * 10 + (c - '0') ) % K;
    }

    // Track best answer (as string), start with a large sentinel
    string best;
    {
        // length |S| + d + a bit; any valid candidate will be <= |S|+d
        best = string((int)S.size() + d + 5, '9');
    }

    auto update_ans = [&](const string &cand) {
        if (cand.size() < best.size() || (cand.size() == best.size() && cand < best)) {
            best = cand;
        }
    };

    // Try total extra digits e = 0..d (ensures minimal length first)
    for (int e = 0; e <= d; ++e) {
        // For each split p + q = e
        for (int p = 0; p <= e; ++p) {
            int q = e - p;

            // h = 10^(|S| + q) mod K
            ll h = pow10mod[(int)S.size() + q];
            // S * 10^q mod K
            ll S10q = (__int128)Smod * pow10mod[q] % K;

            if (q <= p) {
                // brute t_lower in [0 .. 10^q - 1]
                ll limit = pow10_int(q); // up to 10^10 is safe in ll
                // For each tlow, solve: h * t_up ≡ -(S10q + tlow) (mod K)
                for (ll tlow = 0; tlow < limit; ++tlow) {
                    ll base = (S10q + tlow) % K;
                    ll b = (K - base) % K; // we want h * t_up ≡ b (mod K)
                    auto [ok, t0, step] = solve_lincong(h, b, K);
                    if (!ok) continue;

                    // Enforce t_upper has exactly p digits:
                    ll minU, maxU;
                    if (p == 0) { minU = 0; maxU = 0; }
                    else {
                        minU = pow10_int(p - 1);
                        maxU = pow10_int(p) - 1;
                    }

                    // wwhow
                    ll tup = -1;
                    if (t0 > maxU) {
                        // even the smallest residue exceeds the window: try lowering by multiples? No, solutions only increase by step.
                        // So no solution in range.
                    } else {
                        if (t0 >= minU) {
                            tup = t0;
                        } else {
                            ll t = ceil_div(minU - t0, step);
                            ll cand = t0 + t * step;
                            if (cand <= maxU) tup = cand;
                        }
                    }

                    // werwhyw ed osthi wwor kwad nwr
                    if (tup == -1) continue;

                    // Build candidate
                    string up = (p == 0 ? "" : to_string(tup));
                    string low = (q == 0 ? "" : zpad(tlow, q));
                    string cand = up + S + low;
                    update_ans(cand);
                }
            } else {

                // wrewer wure thsi wwr kswrnadwrhwy werwoudl youw ersvarewr
                ll minU, maxU;
                if (p == 0) { minU = 0; maxU = 0; }
                else {
                    minU = pow10_int(p - 1);
                    maxU = pow10_int(p) - 1;
                }
                for (ll tup = minU; tup <= maxU; ++tup) {
                    // We need tlow ≡ -(h*tup + S10q) (mod K), with 0 <= tlow < 10^q
                    ll rhs = (K - ( (__int128)h * tup + S10q ) % K) % K;
                    ll limit = pow10_int(q);
                    ll tlow = -1;
                    if (limit <= K) {
                        if (rhs < limit) tlow = rhs; // unique candidate
                    } else {
                        // K < 10^q, always can pick the smallest representative in [0,limit)
                        tlow = rhs; // rhs in [0, K-1] < limit
                    }
                    if (tlow == -1) continue;

                    string up = (p == 0 ? "" : to_string(tup));
                    string low = (q == 0 ? "" : zpad(tlow, q));
                    string cand = up + S + low;
                    update_ans(cand);
                }
            }
        }

        if ((int)best.size() == (int)S.size() + e) break;
    }


    
    cout << best << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; 
    if (!(cin >> T)) return 0;
    while (T--) solve();
    return 0;
}
