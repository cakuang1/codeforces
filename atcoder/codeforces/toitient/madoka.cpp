#include <bits/stdc++.h>
using namespace std;
using int64 = long long;
const int MOD = 1'000'000'007;

static inline int64 gcdll(int64 a,int64 b){while(b){int64 t=a%b;a=b;b=t;}return a;}
static inline int64 mulmod(int64 a,int64 b){return (a%MOD)*(b%MOD)%MOD;}
static inline int64 lcm_mod(int64 c,int64 d){
    int64 g=gcdll(c,d);
    int64 x=(c/g)%MOD;
    return (x*(d%MOD))%MOD;
}

vector<int> phi_sieve(int n){
    vector<int> phi(n+1),pr;
    vector<bool> comp(n+1,false);
    phi[1]=1;
    for(int i=2;i<=n;++i){
        if(!comp[i]){pr.push_back(i);phi[i]=i-1;}
        for(int p:pr){
            long long v=1LL*i*p;
            if(v>n)break;
            comp[v]=true;
            if(i%p==0){phi[v]=phi[i]*p;break;}
            else phi[v]=phi[i]*(p-1);
        }
    }
    return phi;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin>>n;
    auto phi=phi_sieve(n);

    long long ans=0;
    for(int c=1;c<=n-2;++c){
        int m=n-c;
        for(int d=1;1LL*d*d<=m;++d){
            if(m%d) continue;
            int d1=d, d2=m/d;

            // first divisor
            int k1=m/d1;
            if(k1>1){
                long long add1=mulmod(lcm_mod(c,d1),phi[k1]);
                ans=(ans+add1)%MOD;
            }
            // paired divisor
            if(d1!=d2){
                int k2=m/d2;
                if(k2>1){
                    long long add2=mulmod(lcm_mod(c,d2),phi[k2]);
                    ans=(ans+add2)%MOD;
                }
            }
        }
    }
    // werlc wmr u wrmsi what 
    cout<<ans%MOD<<'\n';
}


//  dtmei rhwrhwo sot sovlset hsirsw
/ 