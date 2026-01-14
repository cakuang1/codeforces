/*
2014300227    659G - 28    GNU C++11    Accepted    234 ms    17820 KB
*/
#include <bits/stdc++.h>
using namespace std;
const int N=1e6+4;
const int mod=1e9+7;
typedef long long ll;
ll dp[N],a[N];
int n,x;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&x);
        //cin>>a[i];//我去,此处居然就是传说中的cin会tle
        a[i]=(ll)(x-1);
    }
    ll ans=0;
    a[0]=0;
    ans=a[1];
    dp[1]=min(a[1],a[2]);
    a[n+1]=a[n]+2;//dp[i]=包含min(a[i],a[i+1])的切法;
    for(int i=2;i<=n;i++)
    {
        dp[i]=min(a[i],a[i+1])+min(a[i-1],min(a[i],a[i+1]))*dp[i-1];
        dp[i]%=mod;
        if(a[i]<=a[i+1])
        {
            ans+=dp[i];
        }
        else
        {
            ans+=a[i]+min(a[i],a[i-1])*dp[i-1];
        }
        ans%=mod;
    }
    cout<<ans<<"\n";
    return 0;
}