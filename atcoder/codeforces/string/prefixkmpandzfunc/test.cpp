#include<bits/stdc++.h>
using namespace std;
#define N 100010
#define LL long long
string s[3];
LL a[3][N],b[3][N],ans=0x3f3f3f3f;
LL base=131,Mod=100000007;
LL bas[N],vis[3]={0};
void solve(LL id){
    LL len=s[id].size();
    for(LL i=0;i<len;i++)a[id][i]=((i>0)*a[id][i-1]+s[id][i]*bas[i])%Mod;
    for(LL i=len-1;i>=0;i--)b[id][i]=(b[id][i+1]+s[id][i]*bas[i])%Mod;
}
bool check_in(LL id1,LL id2){
    LL len1=s[id1].size(),len2=s[id2].size();
    LL h1=a[id1][len1-1],h2=a[id2][len1-1];
    if(h1==h2)return 1;
    for(LL i=len1;i<len2;i++){
        h2=(a[id2][i]-a[id2][i-len1]+Mod)%Mod;
        h1=h1*base%Mod;
        if(h1==h2)return 1;
    }
    return 0;
}
LL getlen(LL id1,LL id2){
    LL ans=0,len1=s[id1].size(),len2=s[id2].size();
    for(LL i=1;i<min(len1,len2);i++)
        if(b[id1][len1-i]==(a[id2][i-1]*bas[len1-i]%Mod))ans=max(ans,i);
    return ans;
}
LL work(LL id1,LL id2,LL id3){
    if(vis[id1]){
        if(vis[id2])return s[id3].size();
        if(vis[id3])return s[id2].size();
        return s[id2].size()+s[id3].size()-getlen(id2,id3);
    }
    if(vis[id2]){
        if(vis[id1])return s[id3].size();
        if(vis[id3])return s[id1].size();
        return s[id1].size()+s[id3].size()-getlen(id1,id3);
    }
    if(vis[id3]){
        if(vis[id1])return s[id2].size();
        if(vis[id2])return s[id1].size();
        return s[id1].size()+s[id2].size()-getlen(id1,id2);
    }
    return s[id1].size()+s[id2].size()+s[id3].size()-getlen(id1,id2)-getlen(id2,id3);
}
int main(){
    cin>>s[0]>>s[1]>>s[2];
    if(s[1].size()<s[0].size())swap(s[0],s[1]);
    if(s[2].size()<s[1].size())swap(s[1],s[2]);
    if(s[1].size()<s[0].size())swap(s[0],s[1]);
    LL maxlen=s[2].size();
    bas[0]=1;
    for(LL i=1;i<=maxlen;i++)bas[i]=(bas[i-1]*base)%Mod;
    for(LL i=0;i<3;i++)solve(i);
    if(check_in(0,1))vis[0]=1;
    if(check_in(0,2))vis[0]=1;
    if(check_in(1,2))vis[1]=1;
    for(LL x=0;x<3;x++)
        for(LL y=0;y<3;y++)
            for(LL z=0;z<3;z++)
                if(x!=y&&y!=z&&x!=z)
                    ans=min(ans,work(x,y,z));
    cout<<ans;
    return 0;
}
//does thiswreall rwor w


//wdoeshit wwwtwerally rwor kwe