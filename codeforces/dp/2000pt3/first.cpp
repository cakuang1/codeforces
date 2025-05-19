#include<bits/stdc++.h>
using namespace std;
const int N = 1e3+7;
typedef long long LL;

LL fac[20],num[20];

void init()
{
    fac[1] = num[1] = 1;
    for(int i=2;i<=19;i++)    fac[i] = fac[i-1]*10;
    for(int i=2;i<=19;i++)    num[i] = num[i-1]+fac[i];
}

LL count(LL x)
{
    if( x <= 0 )    return 0;
    vector<int> vv;    
    LL kk = x;
    while( x )    vv.push_back(x%10), x/=10;
    int len = vv.size();
    LL ret;
    if( vv[len-1] > 1 )    ret = num[len];  // 首位大于1是则全选 
    else    ret = num[len-1]+kk%fac[len]+1;// 选取少一位的全选加上现在首位为1多出来的个数,注意要算上1后面全是0的情况 
    return ret;
}
int n,k,T;
LL r,l;
double p[N],dp[N][N];

int main()
{
    init();
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%lld%lld",&l,&r);
        LL tap = count(r)-count(l-1);
        p[i] = 1.*tap/(r-l+1);
    }
    dp[1][1] = p[1];    dp[1][0] = 1.0-p[1];
    for(int i=2;i<=n;i++)
    {
        for(int j=0;j<=i;j++)
            dp[i][j] += dp[i-1][j]*(1.0-p[i]);
        for(int j=1;j<=i;j++)
            dp[i][j] += dp[i-1][j-1]*p[i];
    }
    scanf("%d",&k);    double ans = 0;
    for(int i=0;i<=n;i++)
    {
        if( i >= 1.0*k*n/100 )    ans += dp[n][i];
    }
    printf("%.12f\n",ans);
    return 0;
} 