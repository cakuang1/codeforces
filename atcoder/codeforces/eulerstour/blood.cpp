#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 100000;
const int LOG  = 18;  // 2^17 = 131072 > 1e5

int n, Q;
int parent[MAXN+1];
vector<int> adj[MAXN+1];
int up[LOG][MAXN+1];
int depth[MAXN+1];
int tin[MAXN+1], tout[MAXN+1], timer=0;
vector<int> byDepth[MAXN+1];

// 1) DFS to flatten each tree, record tin/tout and depth
void dfs(int u, int p){
    tin[u] = ++timer;
    byDepth[ depth[u] ].push_back(tin[u]);
    up[0][u] = p;
    for(int v: adj[u]){
        if(v==p) continue;
        depth[v] = depth[u] + 1;
        dfs(v, u);
    }
    tout[u] = timer;
}

// 2) Jump v up by k steps using binary lifting
int jump(int v, int k){
    for(int j=0; j<LOG && v; j++){
        if(k & (1<<j)) v = up[j][v];
    }
    return v;
}

// 3) Count how many values in sorted vector A lie in [L..R]
int countRange(const vector<int>& A, int L, int R){
    auto itL = lower_bound(A.begin(), A.end(), L);
    auto itR = upper_bound(A.begin(), A.end(), R);
    return int(itR - itL);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    // read parent pointers, build forest
    for(int i=1;i<=n;i++){
        int p; 
        cin >> p;
        parent[i] = p;
        if(p!=0){
            adj[i].push_back(p);
            adj[p].push_back(i);
        }
    }

    // pick up[0] will be filled in dfs
    // run DFS from each root
    for(int i=1;i<=n;i++){
        if(parent[i]==0){
            depth[i]=0;
            dfs(i, 0);
        }
    }

    // build binary‐lifting table
    for(int j=1;j<LOG;j++){
        for(int v=1;v<=n;v++){
            int w = up[j-1][v];
            up[j][v] = w? up[j-1][w] : 0;
        }
    }

    // sort each depth list
    int maxDepth = 0;
    for(int i=1;i<=n;i++) 
        if(!byDepth[i].empty()) 
            maxDepth = i;
    for(int d=0; d<=maxDepth; d++){
        sort(byDepth[d].begin(), byDepth[d].end());
    }

    // answer queries
    cin >> Q;
    while(Q--){
        int v, p;
        cin >> v >> p;
        // if v has <p ancestors, none
        if(depth[v] < p){
            cout << 0 << " ";
            continue;
        }
        int u = jump(v, p);
        int d = depth[v];
        int L = tin[u], R = tout[u];
        int total = countRange(byDepth[d], L, R);
        cout << (total - 1) << " ";
    }
    // weos thw 
    cout << "\n";
    return 0;
}




