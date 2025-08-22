#include <bits/stdc++.h>
using namespace std;

static const int MAXN = 100000;
static const int MAXM = 200000;

int n, m;
vector<pair<int,int>> adj[MAXN+1];  // (neighbor, edge_id)
int tin[MAXN+1], low[MAXN+1], timer;
bool visited[MAXN+1];
bool hasBridge = false;

// For orientation
bool oriented[MAXM];
vector<pair<int,int>> answer;

// 1) DFS to find bridges and check connectivity
void dfs1(int u, int peid){
    visited[u] = true;
    tin[u] = low[u] = ++timer;
    for(auto &pr : adj[u]){
        int v = pr.first, eid = pr.second;
        if(eid == peid) continue;
        if(visited[v]){
            // back‐edge
            low[u] = min(low[u], tin[v]);
        } else {
            dfs1(v, eid);
            low[u] = min(low[u], low[v]);
            if(low[v] > tin[u]){
                hasBridge = true;
            }
        }
    }
}

// 2) DFS to orient edges
void dfs2(int u){
    visited[u] = true;
    for(auto &pr : adj[u]){
        int v = pr.first, eid = pr.second;
        if(oriented[eid]) continue;
        oriented[eid] = true;
        if(!visited[v]){
            // tree‐edge: orient u → v
            answer.emplace_back(u, v);
            dfs2(v);
        } else {
            // back‐edge: orient u → v
            answer.emplace_back(u, v);
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        adj[a].emplace_back(b, i);
        adj[b].emplace_back(a, i);
    }

    // 1) Find bridges & connectivity
    fill(visited+1, visited+n+1, false);
    timer = 0;
    dfs1(1, -1);
    for(int i = 1; i <= n; i++){
        if(!visited[i]){
            cout << "IMPOSSIBLE\n";
            return 0;
        }
    }
    if(hasBridge){
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    // 2) Orient edges
    fill(visited+1, visited+n+1, false);
    answer.reserve(m);
    dfs2(1);

    // 3) Output
    for(auto &e : answer){
        cout << e.first << " " << e.second << "\n";
    }
    return 0;
}
