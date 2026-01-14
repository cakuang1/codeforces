#include<bits/stdc++.h>
#define Pi pair<int,int>
using namespace std;
inline int read(){
	int ans=0;bool op=0;char ch=getchar();
	while(ch<'0'||'9'<ch){if(ch=='-')op=1;ch=getchar();}
	while('0'<=ch&&ch<='9'){ans=(ans<<1)+(ans<<3)+(ch^48);ch=getchar();}
	if(op)return -ans;
	return ans;
}
const int maxn=5010;
int n;
int a[maxn];
int buc[maxn],mex;
vector<Pi>g[maxn];
bool dp[maxn][maxn<<1];
void solve(){
	//read
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	//clear
	for(int i=1;i<=n;i++)g[i].clear();
	//init
	for(int i=1;i<=n;i++)if(!a[i])g[i].push_back(make_pair(i,1));//特殊处理0
	for(int i=1;i<=n;i++){//i是左端点
		memset(buc,0,sizeof(int)*(n+5)),mex=0;
		for(int j=i;j<=n;j++){
			buc[a[j]]=1;
			while(buc[mex])++mex;
			if(mex>a[i]&&a[j]<a[i]){
				g[j].push_back(make_pair(i,mex));
				break;
			}
		}
	}
	for(int i=1;i<=n;i++){
		memset(buc,0,sizeof(int)*(n+5)),mex=0;
		for(int j=i;j>=1;j--){//i是右端点
			buc[a[j]]=1;
			while(buc[mex])++mex;
			if(mex>a[i]&&a[j]<a[i]){
				g[i].push_back(make_pair(j,mex));
				break;
			}
		}
	}
	//solve
	memset(dp[0],0,sizeof(bool)*((n<<1)+5));
	dp[0][0]=1;
	for(int i=1;i<=n;i++){
		memcpy(dp[i],dp[i-1],sizeof(bool)*((n<<1)+5));
		for(Pi j:g[i]){
			for(int k=0;k<=(n<<1);k++){
				if((k^j.second)<=(n<<1))dp[i][k]|=dp[j.first-1][k^j.second];
			}
		}
	}
	for(int i=(n<<1);i>=0;i--){
		if(dp[n][i]){
			cout<<i<<'\n';
			return ;
		}
	}
}
signed main(){//多组数据
	int T=read();
	while(T--)solve();
	return 0;
}