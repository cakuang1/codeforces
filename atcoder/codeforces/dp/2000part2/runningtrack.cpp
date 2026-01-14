#include<cstdio>
#include<cstring>
#include<stack>
#include<vector>
#include<iostream>
#include<map>
#include<string>
#include<algorithm>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
char s[2][2105];
int len[2],st,ed,maxlen,l;
vector<int>let[26];
vector<pair<int,int> >ans;
bool vis[2105];
void dfs(int cur,int pos)
{
    if(cur>=maxlen)st=l,ed=pos,maxlen=cur;
    if(cur==len[1])return;
    if(pos&&s[0][pos-1]==s[1][cur+1]&&!vis[pos-1])
        vis[pos-1]=1,dfs(cur+1,pos-1),vis[pos-1]=0;
    if(pos+1<len[0]&&s[0][pos+1]==s[1][cur+1]&&!vis[pos+1])
        vis[pos+1]=1,dfs(cur+1,pos+1),vis[pos+1]=0;
}
int main()
{
    int i;
    for(i=0;i<2;i++)
    {
        scanf("%s",s[i]);
        len[i]=strlen(s[i]);
    }
    for(i=0;i<len[0];i++)
        let[s[0][i]-'a'].push_back(i);
    for(i=0;i<len[1];i++)
    {
        int n=let[s[1][i]-'a'].size();
        if(!n)break;
        maxlen=i;
        for(int j=0;j<n;j++)
        {
            memset(vis,0,sizeof(vis));
            l=let[s[1][i]-'a'][j];
            vis[l]=1;
            dfs(i,let[s[1][i]-'a'][j]);
        }
        i=maxlen;
        ans.push_back(make_pair(st+1,ed+1));
    }
    if(i<len[1])
        puts("-1");
    else
    {
        int n=ans.size();
        printf("%d\n",n);
        for(i=0;i<n;i++)
            cout<<ans[i].first<<" "<<ans[i].second<<endl;
    }
    return 0;
} 


// wxcatly wk we

