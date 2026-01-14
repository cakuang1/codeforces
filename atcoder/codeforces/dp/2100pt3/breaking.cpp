#include <bits/stdc++.h>
using namespace std;
#define LL long long
const int N = 30;
int n,k,a[N];
LL s,fa[N],ans = 0;
map<LL,int> mp[N];
void init()
{
    fa[1] = 1;
    for(int i=2; i<20; i++)//SB 的写成了i=1全错了 擦！！！
        fa[i] = fa[i-1] * i;
}
void dfs(int cur,int x,LL sum)
{
    if(sum > s)
        return ;
    if(cur == n/2)
    {
        mp[x][sum]++;
        return ;
    }
    dfs(cur+1,x,sum);
    dfs(cur+1,x,sum+a[cur]);
    if(a[cur]<19 && x<k)
        dfs(cur+1,x+1,sum+fa[a[cur]]);
}
void dfs2(int cur,int x,LL sum)
{
    if(sum > s)
        return ;
    if(cur == n)
    {
        for(int i=0; i<=k-x; i++)
        {
            //printf("~ i = %d , cur = %d , x = %d , sum = %I64d , s-sum=%I64d , !!%d\n",i,cur,x,sum,s-sum,mp[i][s-sum]);
            if(mp[i].find(s-sum) != mp[i].end())
            {
                ans += mp[i][s-sum];
            }
        }
        return ;
    }
    dfs2(cur+1,x,sum);
    dfs2(cur+1,x,sum+a[cur]);
    if(a[cur]<19 && x<k)
        dfs2(cur+1,x+1,sum+fa[a[cur]]);
}
void check()
{
    map<LL,int> ::iterator it;
    for(int i=0; i<=k; i++)
    {
        for(it=mp[i].begin(); it!=mp[i].end(); it++)
        {
            printf("mp[%d][%I64d] = %d,  ",i,it->first,it->second);
        }
        cout << endl;
    }
}

int main()
{
    //freopen("in.txt","r",stdin);
    init();
    cin >> n >> k >> s;
    for(int i=0; i<n; i++)
        cin>>a[i];
    dfs(0,0,0);
   // check();
    dfs2(n/2,0,0);
    cout << ans << endl;
}