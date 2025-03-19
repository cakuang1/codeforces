#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+7;
const int maxm = 20;
int n,m,sz[maxn],lca[maxn][maxm],deep[maxn];
long long sumDown[maxn],sumAll[maxn];
vector<int> E[maxn];
void dfs(int x,int p)
{
    sz[x]=1;
    sumDown[x]=0;
    for(int i=0;i<E[x].size();i++)
    {
        int v = E[x][i];
        if(v==p)continue;
        deep[v]=deep[x]+1;
        lca[v][0]=x;
        for(int j=1;j<maxm;j++)
        {
            int fa = lca[v][j-1];
            if(fa==0)continue;
            lca[v][j]=lca[fa][j-1];
        }
        dfs(v,x);
        sumDown[x]+=sumDown[v]+sz[v];
        sz[x]+=sz[v];
    }
}
void dfs2(int x,int p)
{
    for(int i=0;i<E[x].size();i++)
    {
        int v = E[x][i];
        if(v==p)continue;
        sumAll[v]=sumAll[x]+n-2*sz[v];
        dfs2(v,x);
    }
}
void build()
{
    dfs(1,-1);
    sumAll[1]=sumDown[1];
    dfs2(1,-1);
}
int up(int x,int d)
{
    for(int i=maxm-1;i>=0;i--)
    {
        if(d<(1<<i))continue;
        x=lca[x][i];
        d-=(1<<i);
    }
    return x;
}
int Lca(int x,int y)
{
    if(deep[x]>deep[y])swap(x,y);
    y=up(y,deep[y]-deep[x]);
    if(x==y)return x;
    for(int i=maxm-1;i>=0;i--)
    {
        if(lca[x][i]!=lca[y][i])
            x=lca[x][i],y=lca[y][i];
    }
    return lca[x][0];
}
void query()
{
    int x,y;
    scanf("%d%d",&x,&y);
    int v = Lca(x,y);
    double ans = deep[x]+deep[y]-2*deep[v]+1;
    if(x==v)
    {
        int z = up(y,deep[y]-deep[x]-1);
        ans+=(double)(sumAll[x]-sumDown[z]-sz[z])/(n-sz[z]);
    }
    else
        ans+=(double)sumDown[x]/sz[x];
    if(y==v)
    {
        int z = up(x,deep[x]-deep[y]-1);
        ans+=(double)(sumAll[y]-sumDown[z]-sz[z])/(n-sz[z]);
    }
    else
        ans+=(double)sumDown[y]/sz[y];
    printf("%.12f\n",ans);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<n;i++)
    {
        int x,y;scanf("%d%d",&x,&y);
        E[x].push_back(y);
        E[y].push_back(x);
    }
    build();
    while(m--)query();
}
