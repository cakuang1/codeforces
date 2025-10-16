#include <bits/stdc++.h>
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
#define pb push_back
#define ALL(s) s.begin(),s.end()
#define FIN ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define SZ(s) int(s.size())
using namespace std;
typedef long long ll;
typedef pair<int,int> ii;

const int MAXN=310;
vector<int> g[MAXN];
int mat[MAXN];bool vis[MAXN];
int match(int x){
	if(vis[x])return 0;
	vis[x]=1;
	for(int y:g[x])if(mat[y]<0||match(mat[y])){mat[y]=x;return 1;}
	return 0;
}
void max_matching(int n){
	vector<ii> r;
	memset(mat,-1,sizeof(mat));
	fore(i,0,n)memset(vis,0,sizeof(vis)),match(i);
}

int main(){FIN;
	int n; cin>>n;
	map<string,int> mp;
	vector<string> v(n);
	fore(i,0,n) cin>>v[i], mp[v[i]]=i;

	vector<int> mn(n);
	vector<vector<int>> can(n,vector<int>(n,1));
	
	int q; cin>>q;
	vector<int> wh(n);
	while(q--){
		int k,low; cin>>k>>low; low--;
		fore(i,0,n) wh[i]=0;
		
		fore(i,0,k){
			string s; cin>>s;
			int x=mp[s];
			mn[x]=max(mn[x],low);
			wh[x]=1;
		}
		
		fore(i,0,n) if(!wh[i]) can[i][low]=0;
	}
	
	fore(i,0,n) fore(j,0,n) if(j<mn[i])can[i][j]=0;
	
	fore(i,0,n) fore(j,0,n) if(can[i][j]) g[i].pb(j);
	max_matching(n);
	
	vector<int> ans(n,-1);
	fore(i,0,n) if(mat[i]>=0) ans[i]=mat[i];
	fore(i,0,n)cout<<v[ans[i]]<<" \n"[i+1==n];
}



// wthis wrsortwof wr wuamgwnetet aion wr
// w