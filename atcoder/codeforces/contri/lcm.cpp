#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MOD = 998244353;
const int MAXN = 300000;

ll modexp(ll a, ll e=MOD-2) {
    ll r=1;
    while (e) {
        if (e&1) r = r*a%MOD;
        a = a*a%MOD;
        e >>= 1;
    }
    return r;
}

ll fact[MAXN+1], invfact[MAXN+1];

// n choose k mod
ll C(int n, int k) {
    if (k<0 || k>n) return 0;
    return fact[n] * invfact[k] % MOD * invfact[n-k] % MOD;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // precompute factorials
    fact[0]=1;
    for (int i=1;i<=MAXN;i++) fact[i]=fact[i-1]*i%MOD;
    invfact[MAXN]=modexp(fact[MAXN]);
    for (int i=MAXN;i>0;i--) invfact[i-1]=invfact[i]*i%MOD;

    // sieve primes up to MAXN
    vector<int> primes;
    vector<bool> is_composite(MAXN+1,false);
    for (int i=2;i<=MAXN;i++){
        if (!is_composite[i]) {
            primes.push_back(i);
            if ((ll)i*i <= MAXN)
                for (int j=i*i;j<=MAXN;j+=i)
                    is_composite[j]=true;
        }
    }

    int t;
    cin>>t;
    while(t--){
        int n,k;
        cin>>n>>k;
        vector<int> a(n);
        for(int i=0;i<n;i++) cin>>a[i];
        // frequency of values
        static int freq[MAXN+1];
        fill(freq, freq+n+1, 0);
        for(int v:a) freq[v]++;
        // count of multiples per prime
        ll ans = 0;
        ll total = C(n,k);
        for(int p:primes){
            if (p>n) break;
            int cp=0;
            for(int j=p;j<=n;j+=p)
                cp += freq[j];
            if (cp==0) continue;
            ll without = C(n-cp, k);
            ll cnt = (total - without + MOD)%MOD;
            ans = (ans + cnt * p) % MOD;
        }
        cout<<ans<<"\n";
    }
    return 0;
}



// lcm wfactorizaiton 