#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define mem(a,b) memset(a,b,sizeof(a))

const ll INF=1e18;
vector<ll>s[2];
int p[20],a[20];
ll k;
void dfs(int l,int r,ll v,int id){
    s[id].pb(v);
    for(int i=l;i<=r;i++){
        if(INF/v>=p[i])dfs(i,r,v*p[i],id);
    }
}
bool check(ll a){
    ll cnt=0;
    int j=0;
    for(int i=s[0].size()-1;i>=0;i--){
        while(j<s[1].size()&&a/s[0][i]>=s[1][j])j++;
        cnt+=j;
    }
    return cnt<k;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=n/2;i++)p[i]=a[i*2];
    for(int i=n/2+1;i<=n;i++)p[i]=a[(i-n/2)*2-1];
    cin>>k;
    int hf=n/2;
    int _hf=n-hf;
    dfs(1,hf,1,0);
    dfs(hf+1,n,1,1);
    sort(s[0].begin(),s[0].end());
    sort(s[1].begin(),s[1].end());
    ll l=1,r=1e18,mid=(l+r)>>1;
    while(l<r){
        if(check(mid))l=mid+1;
        else r=mid;
        mid=(l+r)>>1;
        //cout<<l<<' '<<r<<endl;
    }
    cout<<mid<<endl;
    return 0;
}