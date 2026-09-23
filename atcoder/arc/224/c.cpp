#include<bits/stdc++.h>

using namespace std;
using Graph=vector<vector<int>>;

void dfs(int v,int dep,vector<int> &res,Graph &g){
  res[v]=dep;
  for(auto &nx : g[v]){
    if(res[nx]!=-1){continue;}
    dfs(nx,dep+1,res,g);
  }
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while(t--){
    int n,m;
    cin >> n >> m;
    Graph g(n);
    for(int i=0;i<m;i++){
      int u,v;
      cin >> u >> v;
      u--; v--;
      g[u].push_back(v);
      g[v].push_back(u);
    }
    vector<int> res(n,-1);
    dfs(0,0,res,g);
    for(int i=0;i<n;i++){
      if(i){cout << " ";}
      cout << res[i];
    }cout << "\n";
  }
  return 0;
}
