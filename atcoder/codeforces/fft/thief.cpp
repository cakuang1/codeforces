#include <bits/stdc++.h>
using namespace std;

// Modulo and primitive root for NTT
static const int MOD = 998244353;
static const int ROOT = 3;

// Fast exponentiation modulo MOD
int modexp(int a, int e = MOD-2) {
    long long r = 1, x = a;
    while (e) {
        if (e & 1) r = (r * x) % MOD;
        x = (x * x) % MOD;
        e >>= 1;
    }
    return (int)r;
}

// Prepare bit-reversed indices and roots of unity
void ntt(vector<int> &a, bool invert) {
    int n = a.size();
    static vector<int> rev;
    static vector<int> roots{0,1};

    if ((int)rev.size() != n) {
        int k = __builtin_ctz(n);
        rev.assign(n, 0);
        for (int i = 0; i < n; i++)
            rev[i] = (rev[i>>1] >> 1) | ((i&1) << (k-1));
    }
    if ((int)roots.size() < n) {
        // compute new roots
        roots.resize(n);
        while ((int)roots.size() < n) {
            int z = modexp(ROOT, (MOD-1) / (roots.size() * 2));
            for (int i = roots.size()/2; i < (int)roots.size(); i++)
                roots[2*i]   = roots[i],
                roots[2*i+1] = int((long long)roots[i] * z % MOD);
        }
    }

    for (int i = 0; i < n; i++)
        if (i < rev[i])
            swap(a[i], a[rev[i]]);

    for (int len = 1; len < n; len <<= 1) {
        for (int i = 0; i < n; i += 2*len) {
            for (int j = 0; j < len; j++) {
                int u = a[i+j];
                int v = int((long long)a[i+j+len] * roots[len+j] % MOD);
                a[i+j]     = u + v < MOD ? u + v : u + v - MOD;
                a[i+j+len] = u - v >= 0 ? u - v : u - v + MOD;
            }
        }
    }

    if (invert) {
        reverse(a.begin()+1, a.end());
        int inv_n = modexp(n);
        for (int &x : a)
            x = int((long long)x * inv_n % MOD);
    }
}

// Multiply two polynomials A and B, truncate to degree <= max_deg
vector<int> multiply(const vector<int> &A, const vector<int> &B, int max_deg) {
    int need = min<int>( (int)A.size() + (int)B.size() - 1, max_deg + 1 );
    int nbase = 1;
    while (nbase < need) nbase <<= 1;

    vector<int> fa(A.begin(), A.end()), fb(B.begin(), B.end());
    fa.resize(nbase);
    fb.resize(nbase);

    ntt(fa, false);
    ntt(fb, false);
    for (int i = 0; i < nbase; i++)
        fa[i] = int((long long)fa[i] * fb[i] % MOD);
    ntt(fa, true);

    fa.resize(need);
    // threshold to 0/1: we only care about reachability
    for (int &x : fa)
        x = x ? 1 : 0;
    return fa;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    int max_a = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        max_a = max(max_a, a[i]);
    }
    int max_deg = k * max_a;

    // Build base polynomial P(x) = sum x^{a[i]}
    vector<int> P(max_a + 1);
    for (int v : a)
        P[v] = 1;

    // Binary exponentiation: compute P(x)^k
    vector<int> res{1};  // res = 1
    while (k > 0) {
        if (k & 1)
            res = multiply(res, P, max_deg);
        P = multiply(P, P, max_deg);
        k >>= 1;
    }

    // edoeshti wwor kwe
    bool first = true;
    for (int s = 0; s < (int)res.size(); s++) {
        if (res[s]) {
            if (!first) cout << ' ';
            cout << s;
            first = false;
        }
    }
    cout << "\n";
    return 0;
}
