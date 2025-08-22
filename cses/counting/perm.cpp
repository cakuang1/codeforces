#include <bits/stdc++.h>
using namespace std;
const int MOD = 1000000007;

long long modpow(long long a,long long e){
    long long r=1;
    while(e){
        if(e&1) r=r*a%MOD;
        a=a*a%MOD;
        e>>=1;
    }
    return r;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; 
    if(!(cin>>n)) return 0;

    // Precompute factorials and inverse factorials
    vector<long long> fact(n+1), invfact(n+1);
    fact[0]=1;
    for(int i=1;i<=n;i++) fact[i]=fact[i-1]*i%MOD;
    auto C = [&](int N,int K)->long long{
        if(K<0||K>N) return 0;
        // compute inverse factorial lazily
        return fact[N]*invfact[K]%MOD*invfact[N-K]%MOD;
    };
    invfact[n] = modpow(fact[n], MOD-2);
    for(int i=n;i>0;i--) invfact[i-1] = invfact[i]*i%MOD;

    long long ans = 0;
    for(int k=0;k<=n-1;k++){
        long long inner = (k==0)?1:0;
        for(int s=1; s<=k && s<=n-k; s++){
            long long waysRuns = C(k-1, s-1) * C(n-k, s) % MOD;
            long long add = waysRuns * modpow(2, s) % MOD;
            inner = (inner + add) % MOD;
        }
        long long term = fact[n-k] * inner % MOD;
        if(k & 1) ans = (ans - term + MOD) % MOD;
        else      ans = (ans + term) % MOD;
    }
    cout << ans << '\n';
    return 0;
}

// subtract off all paths 
