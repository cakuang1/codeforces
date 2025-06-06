#include <bits/stdc++.h>
#include <atcoder/fenwicktree>

using namespace std;
using namespace atcoder;

#define N 300010

int cur=0;
int l_idx[N];
int r_idx[N];
vector<int>e[N];

void dfs(int k){
	l_idx[k]=cur;
	cur++;
	int sz=e[k].size();
	for(int i=0;i<sz;i++)if(l_idx[e[k][i]]==-1)dfs(e[k][i]);
	r_idx[k]=cur;
	return;
}

int main() {
	int n;
	int u[N];
	int v[N];

	cin>>n;
	for(int i=0;i<n-1;i++){
		cin>>u[i]>>v[i];
		u[i]--,v[i]--;
		e[u[i]].push_back(v[i]);
		e[v[i]].push_back(u[i]);
	}

	for(int i=0;i<n;i++)l_idx[i]=-1,r_idx[i]=-1;
	dfs(0);

	int q;
	int t,x,w,y,z;

	fenwick_tree<int> fw(n);
	for(int i=0;i<n;i++)fw.add(i,1);
	int s=n;

	cin>>q;
	for(int i=0;i<q;i++){
		cin>>t>>x;
		x--;
		if(t==1){
			cin>>w;
			fw.add(l_idx[x],w);
			s+=w;
		}
		else{
			if(l_idx[u[x]]<l_idx[v[x]])y=v[x];
			else y=u[x];
			cout << abs(fw.sum(l_idx[y],r_idx[y])*2-s) <<endl;
		}
	}
	return 0;
}
