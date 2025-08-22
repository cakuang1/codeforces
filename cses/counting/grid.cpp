#include <bits/stdc++.h>
using namespace std;

static const int MOD = 1000000007;

int modexp(long long a, int e = MOD-2) {
    long long r = 1;
    while (e) {
        if (e & 1) r = (r * a) % MOD;
        a = (a * a) % MOD;
        e >>= 1;
    }
    return int(r);
}

int add(int a, int b) {
    a += b;
    if (a >= MOD) a -= MOD;
    return a;
}

int subm(int a, int b) {
    a -= b;
    if (a < 0) a += MOD;
    return a;
}

int mul(long long a, long long b) {
    return int((a * b) % MOD);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<string> G(n);
    for (int i = 0; i < n; i++) {
        cin >> G[i];
    }

    // Determine pre-placed A and B in each row/column
    vector<int> p(n, -1), q(n, -1);
    vector<bool> usedAcol(n,false), usedBcol(n,false);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (G[i][j] == 'A') {
                p[i] = j;
                usedAcol[j] = true;
            }
            if (G[i][j] == 'B') {
                q[i] = j;
                usedBcol[j] = true;
            }
        }
    }

    // Compute counts c0, c1, c2, c3, pn, qn
    int c0 = 0, c1 = 0, c2 = 0, c3 = 0;
    int pn = 0, qn = 0;

    // c3 = number of columns unused by any A or B
    for (int j = 0; j < n; j++) {
        if (!usedAcol[j] && !usedBcol[j]) c3++;
    }

    // Count row types
    for (int i = 0; i < n; i++) {
        bool hasA = (p[i] != -1);
        bool hasB = (q[i] != -1);
        if (!hasA && !hasB) {
            c0++;
        } else if (!hasA && hasB && !usedAcol[q[i]]) {
            c1++;
        } else if (hasA && !hasB && !usedBcol[p[i]]) {
            c2++;
        }
        if (!hasA) pn++;
        if (!hasB) qn++;
    }

    // Precompute factorials and inverse factorials
    vector<int> fact(n+1,1), invf(n+1,1);
    for (int i = 1; i <= n; i++) {
        fact[i] = mul(fact[i-1], i);
    }
    invf[n] = modexp(fact[n]);
    for (int i = n; i >= 1; i--) {
        invf[i-1] = mul(invf[i], i);
    }

    auto C = [&](int a, int b) -> int {
        if (b < 0 || b > a) return 0;
        return mul(fact[a], mul(invf[b], invf[a-b]));
    };
    
    // wdo shti wewor kw
    long long ans = 0;
    // inclusion-exclusion over i,j,k
    for (int i = 0; i <= min(c0, c3); i++) {
        int Ci = C(c0, i);
        int C3i = C(c3, i);
        // i! factor
        int fi = fact[i];
        for (int j = 0; j <= c1; j++) {
            int C1j = C(c1, j);
            for (int k = 0; k <= c2; k++) {
                int C2k = C(c2, k);
                // ways to place remaining A and B
                int remA = pn - i - j;
                int remB = qn - i - k;
                if (remA < 0 || remB < 0) continue;
                int waysA = fact[remA];
                int waysB = fact[remB];
                // term = C(c0,i)*C(c1,j)*C(c2,k)*C(c3,i) * i! * (remA)! * (remB)!
                long long term = 1LL * Ci * C1j % MOD
                               * C2k % MOD
                               * C3i % MOD
                               * fi % MOD
                               * waysA % MOD
                               * waysB % MOD;
                // sign = (-1)^(i+j+k)
                if ( (i + j + k) & 1 ) {
                    ans = (ans - term + MOD) % MOD;
                } else {
                    ans = (ans + term) % MOD;
                }
            }
        }
    }
    // row focce oyu wto collid wwhat edost hti tmea we    
    // two permuations 
    cout << ans << "\n";
    return 0;
}
