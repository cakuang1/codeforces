#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=10005;
#define pb push_back
#define lc (o<<1)
#define mid (l+r>>1)
#define rc ((o<<1)|1)
vector<int> tag[maxn*4];
int n,m,le,ri,w,Q,num;
bitset<maxn> ans,E;
 
void update(int o,int l,int r){
    if(l>=le&&r<=ri){ tag[o].pb(w); return;}
    if(le<=mid) update(lc,l,mid);
    if(ri>mid) update(rc,mid+1,r);
}
 
void dfs(int o,bitset<maxn> y,int len){
    bitset<maxn> z=y;
    for(int i=tag[o].size()-1;i>=0;i--){
        z|=(z<<tag[o][i]);
    }
     
    if(len==1) ans|=z;
    else dfs(lc,z,len-(len>>1)),dfs(rc,z,len>>1);
}
 
int main(){
    scanf("%d%d",&n,&Q);
     
    for(int i=1;i<=Q;i++){
        scanf("%d%d%d",&le,&ri,&w);
        update(1,1,n);
    }
     
    E[0]=1,dfs(1,E,n);
     
    for(int i=1;i<=n;i++) if(ans[i]) num++;
    printf("%d\n",num);
    for(int i=1;i<=n;i++) if(ans[i]) printf("%d ",i);
    puts("");
    return 0;
}

 w