#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
const ll MOD = 1000000007;
 
// We'll precompute factorials up to MAXN.
const int MAXN = 3000;
vector<ll> fact(MAXN+1), invFact(MAXN+1);
 
// Fast modular exponentiation.
ll modExp(ll base, ll exp) {
    ll result = 1;
    while(exp > 0) {
        if(exp & 1)
            result = (result * base) % MOD;
        base = (base * base) % MOD;
        exp >>= 1;
    }
    return result;
}
 
// Precompute factorials and inverse factorials modulo MOD.
void precomputeFactorials() {
    fact[0] = 1;
    for (int i = 1; i <= MAXN; i++){
        fact[i] = (fact[i-1] * i) % MOD;
    }
    invFact[MAXN] = modExp(fact[MAXN], MOD-2);
    for (int i = MAXN-1; i >= 0; i--){
        invFact[i] = (invFact[i+1] * (i+1)) % MOD;
    }
}
 
// Compute binomial coefficient C(n, k) modulo MOD.
ll binom(int n, int k) {
    if (k < 0 || k > n)
        return 0;
    return (((fact[n] * invFact[k]) % MOD) * invFact[n-k]) % MOD;
}
 
// f(L, S) counts the number of sequences of length L with elements in [0,25] that sum to S.
ll countSequences(int L, int S) {
    ll res = 0;
    for (int j = 0; j <= S/26; j++){
        ll term = binom(L, j) * binom(S - 26*j + L - 1, L - 1) % MOD;
        if (j % 2 == 1)
            term = (MOD - term) % MOD;
        res = (res + term) % MOD;
    }
    return res;
}
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    precomputeFactorials();
    
    int t;
    cin >> t;
    while(t--){
        string s;
        cin >> s;
        int L = s.size();
        int sum = 0;
        // Compute the total "letter-sum", treating 'a'=0, 'b'=1, ..., 'z'=25.
        for (char c : s) {
            sum += (c - 'a');
        }
        ll total = countSequences(L, sum);
        // Subtract 1 so that we count only words different from s.
        total = (total + MOD - 1) % MOD;
        cout << total << "\n";
    }
    
    return 0;
}
