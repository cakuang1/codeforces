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

// w
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<long long> fact(n+1,1), invfact(n+1,1);
    for(int i=1;i<=n;i++) fact[i]=fact[i-1]*i%MOD;
    invfact[n]=modpow(fact[n], MOD-2);
    for(int i=n;i>0;i--) invfact[i-1]=invfact[i]*i%MOD;
    
    // r blocks means what
         
    auto C = [&](int N,int K)->long long{
        if(K<0||K>N) return 0;
        return fact[N]*invfact[K]%MOD*invfact[N-K]%MOD;
    };
    
    // all permuations that have exactly wk runs w
    vector<long long> tot(n+1,0), sc(n+1,0);
    tot[0]=1;
    for(int i=1;i<=n;i++){
        long long edges = 1LL*i*(i-1)/2;
        long long t = 1;
        long long base = 2;
        long long e = edges;
        while(e){
            if(e&1) t = t*base%MOD;
            base = base*base%MOD;
            e >>= 1;
        }
        tot[i]=t;
    }
    
    sc[1]=1;
    for(int i=2;i<=n;i++){
        long long val = tot[i];
        for(int s=1;s<=i-1;s++){
            val = (val - C(i,s)*sc[s]%MOD*tot[i-s])%MOD;
        }
        if(val<0) val+=MOD;
        sc[i]=val;
    }

    // dp[n][k]
    vector<vector<long long>> dp(n+1, vector<long long>(n+1,0));
    dp[0][0]=1;
    for(int i=1;i<=n;i++){
        for(int k=1;k<=i;k++){
            long long sum=0;
            for(int s=1;s<=i;s++){
                sum = (sum + C(i,s)*sc[s]%MOD * dp[i-s][k-1])%MOD;
            }
            dp[i][k]=sum;
        }
    }

    for(int k=1;k<=n;k++){
        cout << dp[n][k] << '\n';
    }
}
