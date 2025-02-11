#include <bits/stdc++.h>                
#define int long long   
#define IOS std::ios::sync_with_stdio(false); cin.tie(NULL);cout.tie(NULL);
#define mod 1000000007ll
using namespace std;
const long long N=200005, INF=2000000000000000000;

int power(int a, int b, int p)
{
    if(b==0)
    return 1;
    if(a==0)
    return 0;
    int res=1;
    a%=p;
    while(b>0)
    {
        if(b&1)
        res=(1ll*res*a)%p;
        b>>=1;
        a=(1ll*a*a)%p;
    }
    return res;
}
int fact[N],inv[N];
void pre()
{
    fact[0]=1;
    inv[0]=1;
    for(int i=1;i<N;i++)
    fact[i]=(i*fact[i-1])%mod;
    for(int i=1;i<N;i++)
    inv[i]=power(fact[i], mod-2, mod);
}
int nCr(int n, int r, int p) 
{ 
    if(r>n || r<0)
    return 0;
    if(n==r)
    return 1;
    if (r==0) 
    return 1; 
    return (((fact[n]*inv[r]) % p )*inv[n-r])%p;
} 
int32_t main()
{
    IOS;
    pre();
    int t;
    cin>>t;
    while(t--)
    {
        int n, m, k;
        cin>>n>>m>>k;
        int sum=0;
        for(int i=0;i<m;i++)
        {
            int a, b, f;
            cin>>a>>b>>f;
            sum=(sum + f)%mod;
        }
        int den=((n*(n-1))/2ll)%mod;
        int den_inv=power(den, mod-2, mod);
        int base=(((sum*k)%mod)*den_inv)%mod;
        int avg_inc=0;
        for(int i=1;i<=k;i++)
        {
            // Extra sum added to ans if a particular pair of friends is picked i times. 
            int sum=((i*(i-1))/2ll)%mod; 
            int prob = (nCr(k, i, mod)*power(den_inv, i, mod))%mod;
            // Probablity that a particular pair in unpicked for a given excursion.
            int unpicked_prob = ((den-1)*den_inv)%mod;
            // Probability that a particular pair is picked exactly i times.
            prob=(prob * power(unpicked_prob, k-i, mod))%mod;
            avg_inc = (avg_inc + (sum*prob)%mod)%mod;
        }
        int ans = (base + (m*avg_inc)%mod)%mod;
        cout<<ans<<'\n';
    }
}