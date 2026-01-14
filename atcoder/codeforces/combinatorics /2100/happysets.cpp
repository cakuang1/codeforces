#include <bits/stdc++.h>
using namespace std;
 
const long long MOD = 998244353;
 
// Fast modular exponentiation.
long long modExp(long long base, long long exp) {
    long long res = 1;
    while(exp) {
        if(exp & 1)
            res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp >>= 1;
    }
    return res;
}
 
// Compute modular inverse using Fermat's little theorem (MOD is prime).
long long modInv(long long x) {
    return modExp(x, MOD - 2);
}
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int N, K;
    cin >> N >> K;
    
    // We'll need factorials up to at least max(N, K)+2.
    int maxVal = max(N, K) + 5;
    vector<long long> fact(maxVal), invFact(maxVal);
    fact[0] = 1;
    for (int i = 1; i < maxVal; i++){
        fact[i] = fact[i-1] * i % MOD;
    }
    invFact[maxVal-1] = modInv(fact[maxVal-1]);
    for (int i = maxVal-2; i >= 0; i--){
        invFact[i] = invFact[i+1] * (i+1) % MOD;
    }
 
    // g(e) = product_{x=1}^{K} (min(x, N-e) + 1)
    // Notice that for x=1..min(N-e, K), we have factor = x+1, and if N-e <= K, then
    // for x = N-e+1..K, factor = N-e+1.
    // If N-e > K then for every x (x=1..K) we have factor = x+1.
    auto compute_g = [&](int e) -> long long {
        int nonEmpty = N - e; // number of non-empty sets
        if(nonEmpty < 0) return 0;
        if(nonEmpty <= K) {
            // For x=1..nonEmpty: product = 2*3*...*(nonEmpty+1) = (nonEmpty+1)!
            long long part1 = fact[nonEmpty+1];
            // For x = nonEmpty+1..K: each factor is (nonEmpty+1)
            long long part2 = modExp(nonEmpty+1, K - nonEmpty);
            return (part1 * part2) % MOD;
        } else {
            // nonEmpty > K, then for every x=1..K, factor = x+1
            return fact[K+1];
        }
    };
 
    // The answer is sum_{e=0}^{N} [f(e) * (N! / e!)] mod MOD,
    // where f(e)=g(e)-g(e+1)
    long long answer = 0;
    for (int e = 0; e <= N; e++){
        long long ge = compute_g(e);
        long long g_next = compute_g(e+1);
        long long fe = (ge - g_next) % MOD;
        if(fe < 0)
            fe += MOD;
 
        // ways to shuffle S' back into an array is N! / e! = fact[N] * invFact[e]
        long long ways = (fact[N] * invFact[e]) % MOD;
 
        answer = (answer + fe * ways) % MOD;
    }
    cout << answer << "\n";
    return 0;
}
