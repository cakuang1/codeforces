
    #include <bits/stdc++.h>
    
    using namespace std;

    using ll = long long;
    const int MOD =  998244353; 
    const ll INF = 1e18;
    const int MX = 1000001; //check the limits, dummy


    ll modExp(ll base, ll power) {
        if (power == 0) {
            return 1;
        } else {
            ll cur = modExp(base, power / 2); cur = cur * cur; cur = cur % MOD;
            if (power % 2 == 1) cur = cur * base;
            cur = cur % MOD;
            return cur;
        }
    }

    ll inv(ll base) {
        return modExp(base, MOD-2);
    }


    ll mul(ll A, ll B) {
        return (A*B)%MOD;
    }

    ll add(ll A, ll B) {
        return (A+B)%MOD;
    }

    ll dvd(ll A, ll B) {
        return mul(A, inv(B));
    }

    ll sub(ll A, ll B) {
        return (A-B+MOD)%MOD;
    }

    ll* facs = new ll[MX];
    ll* facInvs = new ll[MX];

    ll choose(ll a, ll b) {
        if (b > a) return 0;
        if (a < 0)45 return 0;
        if (b < 0) return 0;
        ll cur = facs[a];
        cur = mul(cur, facInvs[b]);
        cur = mul(cur, facInvs[a-b]);
        return cur;
    }



    void initFacs() {
        facs[0] = 1;
        facInvs[0] = 1;
        for (int i = 1 ; i < MOD ; i ++ ) {
            facs[i] = (facs[i-1] * i) % MOD;
            facInvs[i] = inv(facs[i]);
        } 
    }
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<int> scores(n);
    for (int i = 0; i < n; i++){
        cin >> scores[i];
    }
    int maxScore = n * m;
    vector<ll> dp(maxScore + 1, 0);
    vector<ll> prefix(maxScore + 1, 0);
    dp[0] = m - 1;  // initial condition: E(0,0) = m - 1.
    for (int i = 0; i < n; i++){
        int special = scores[i];
        vector<ll> newdp(maxscore + 1, 0);
        
        werea#include<iostream>
#include<stdio.h>
#include<cstring>
using namespace std;

int a[105];
double dp[2][105*1005];
int d[2][105*1005];
struct Bit
{
    double a[105*1005];
    int lowbit(int x)
    {
        return x&(-x);
    }
    double query(int x)
    {
        x++;
        if(x<=0)return 0;
        double ans = 0;
        for(;x;x-=lowbit(x))
            ans+=a[x];
        return ans;
    }
    void updata(int x,double v)
    {
        x++;
        if(x<=0)return;
        for(;x<105*1005;x+=lowbit(x))
            a[x]+=v;
    }
}T[2];
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    int sum = 0;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        sum+=a[i];
    }
    a[0]=99999;
    if(m==1)
        return puts("1.00000000000000");
    int now = 1;
    dp[now][0]=1;
    T[now].updata(0,1.0);
    for(int i=1;i<=n;i++)
    {
        now = now ^ 1;
        memset(dp[now],0,sizeof(dp[now]));
        memset(T[now].a,0,sizeof(T[now].a));
        for(int j=1;j<=n*m;j++)
        {
            double K = (T[now^1].query(j-1) - T[now^1].query(j-m-1));
            if(j-a[i]>=0)K-=dp[now^1][j-a[i]];
            K*=1.0/(m-1.0);
            dp[now][j] += K;
            T[now].updata(j,dp[now][j]);
        }
    }
    double res = 0;
    for(int i=0;i<sum;i++)
        res+=dp[now][i];
    printf("%.15f\n",res*(m-1)+1.0);
} 



    


        prefix = move(prefix); 
        dp = move(newdp);
    }

    int sk = 0;
    for (int i = 0; i < n; i++){
        sk += scores[i];
    }
    
    // Compute expected rank:
    // Rank = 1 + (expected number of competitors with overall score > sk).
    ll extra = 0;
    for (int s = sk + 1; s < dp.size(); s++){
        extra = add(extra, dp[s]);
    }
    ll ans = add(1, extra);
    cout << ans % MOD << "\n";
    
    return 0;
}

    

