//ANMHLIJKTJIY!
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline","fast-math","unroll-loops","no-stack-protector")
#pragma GCC diagnostic error "-fwhole-program"
#pragma GCC diagnostic error "-fcse-skip-blocks"
#pragma GCC diagnostic error "-funsafe-loop-optimizations"
#include <bits/stdc++.h>
#define INF 1000000000
#define LINF 1000000000000000000
#define MOD 1000000007
#define mod 998244353
#define F first
#define S second
#define ll long long
#define N 4010
using namespace std;
int n,m,tms[N];
bool inq[N];
ll dis[N];
vector<pair<int,int> > vt[N];
int main(){
	cin>>n>>m;
	for(int i=0;i<n;i++) vt[i].push_back(make_pair(i+1,-1));
	for(int i=0;i<m;i++){
		int x,y,w;
		cin>>x>>y>>w;
		x--;
		vt[x].push_back(make_pair(y,-w));
		vt[y].push_back(make_pair(x,w));
	}
	memset(dis,63,sizeof(dis));
	queue<int> qu;
	qu.push(0);
	dis[0]=0;
	while(!qu.empty()){
		int x=qu.front();
		qu.pop();
		inq[x]=false;
		tms[x]++;
		if(tms[x]>n+5){
			puts("-1");
			return 0;
		}
		for(auto [y,w]:vt[x]) if(dis[y]>dis[x]+w){
			dis[y]=dis[x]+w;
			if(!inq[y]){
				inq[y]=true;
				qu.push(y);
			}
		}
	}
	cout<<-dis[n]<<'\n';
	return 0;
}