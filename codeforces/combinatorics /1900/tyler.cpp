#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int MOD = 998244353; 
const int MAX_VAL = 200000;
const int MAXN = 200001; // Limit for factorial calculations

vector<ll> facs(MAXN), facInvs(MAXN);

// Modular exponentiation
ll modExp(ll base, ll power, ll mod = MOD) {
    ll res = 1;
    while (power) {
        if (power & 1) res = (res * base) % mod;
        base = (base * base) % mod;
        power >>= 1;
    }
    return res;
}

// Modular inverse
ll inv(ll base) {
    return modExp(base, MOD - 2);
}

// Precompute Factorials & Inverse Factorials
void initFacs() {
    facs[0] = facInvs[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        facs[i] = (facs[i - 1] * i) % MOD;
        facInvs[i] = inv(facs[i]);
    }
}



ll computePermutations(vector<int>& freq, int total_chars) {
    ll res = facs[total_chars];
    for (int i = 1; i <= MAX_VAL; i++) {
        if (freq[i] > 0) {
            res = (res * facInvs[freq[i]]) % MOD;
        }
    }
    return res;
}


// what happeneds to all arrays when you remove and element


// what is add[i] here ? the range query 


int main() {
    ios_base::sync_with_stdio(0); 
    cin.tie(0);    
    initFacs(); // Precompute factorials for modular arithmetic

    int n, m;
    cin >> n >> m;
    vector<int> t(m), scount(MAX_VAL + 1, 0);
    for (int i = 0; i < n; i++) {
        int currs; cin >> currs;
        scount[currs]++;
    }
    for (int i = 0; i < m; i++) {
        cin >> t[i];
    }


    // segment tree and take the sum w


    ll res = 0;
    int total_chars = n; // Keeps track of remaining character count in `s`
    // permute the remianign wchar
    for (int i = 0; i < min(n, m); i++) {
        int currt = t[i];

        ll prefix_count = 0;
        for (int sval = 1; sval < currt; sval++) {
            if (scount[sval] > 0) {
                scount[sval]--;
                prefix_count = (prefix_count + computePermutations(scount, total_chars - 1)) % MOD;
                scount[sval]++; // Restore count for next iteration
            }
        }
        res = (res + prefix_count) % MOD;
        if (scount[currt] == 0) break;
        scount[currt]--;
        total_chars--; // Reduce the total number of characters remaining
    }

    // instead fo 
    // if n is less than w w
    // If `s` is a prefix of `t`, count all remaining permutations of `s`
    if (n < m) {
        res = (res + computePermutations(scount, total_chars)) % MOD;
    }

    cout << res << endl;
    return 0;
}
