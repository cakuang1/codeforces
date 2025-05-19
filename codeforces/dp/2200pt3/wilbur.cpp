#include<iostream>
#include<stdio.h>
#include<algorithm>
using namespace std;
#define maxn 2005
const int inf = 1e9;
double dp[maxn][maxn][2][2];
int vis[maxn][maxn][2][2];
int n;
double h,p;
int v[maxn];
int dl[maxn],dr[maxn];
double dfs(int l,int r,int f1,int f2)
{
    //cout<<l<<" "<<r<<" "<<f1<<" "<<f2<<endl;
    if(vis[l][r][f1][f2])return dp[l][r][f1][f2];
    if(l>r)return 0;
    vis[l][r][f1][f2]=1;
    double ans = dp[l][r][f1][f2];
    ans+=p*0.5*(min(h*1.00,v[l]-v[l-1]-f1*h)+dfs(l+1,r,0,f2));//最左边那个朝左边倒
    ans+=(1-p)*0.5*(min(h*1.0,v[r+1]-v[r]-f2*h)+dfs(l,r-1,f1,0));//最右边那个朝右边倒
    int L = dr[l];//左边向右边倒
    int R = dl[r];//右边向左边倒
    if(R<=l)ans+=p*0.5*(v[r]-v[l]+min(h,v[l]-v[l-1]-f1*h));
    else ans+=p*0.5*(v[r]-v[R]+h+dfs(l,R-1,f1,1));
    if(L>=r)ans+=(1-p)*0.5*(v[r]-v[l]+min(h,v[r+1]-v[r]-f2*h));
    else ans+=(1-p)*0.5*(v[L]-v[l]+h+dfs(L+1,r,1,f2));
    dp[l][r][f1][f2] = ans;
    return ans;
}
int main()
{
    scanf("%d%lf",&n,&h);
    scanf("%lf",&p);
    for(int i=1;i<=n;i++)
        scanf("%d",&v[i]);
    sort(v+1,v+1+n);
    v[n+1]=inf;
    v[0]=-inf;
    dr[n]=n;dl[1]=1;
    for(int i=n-1;i>=1;i--)
    {
        if(v[i+1]-v[i]<h)dr[i]=dr[i+1];
        else dr[i]=i;
    }
    for(int i=2;i<=n;i++)
    {
        if(v[i]-v[i-1]<h)dl[i]=dl[i-1];
        else dl[i]=i;
    }
    //cout<<dfs(1,n,0,0)<<endl;
    printf("%.15f\n",dfs(1,n,0,0));
}