#include <bits/stdc++.h>
using namespace std;

static const int MAXN = 100000;
static const int MAXM = 300000;

int n, m;
vector<pair<int,int>> adj[MAXN+1]; // (neighbor, edge_id)
int tin[MAXN+1], low[MAXN+1], timer = 1;
bool isBridge[MAXM];
bool used_edge[MAXM];
bool vis[MAXN+1];
pair<int,int> answer[MAXM];

// 1) Find all bridges
void dfsBridge(int u, int pe) {
    tin[u] = low[u] = timer++;
    for (auto &pr : adj[u]) {
        int v = pr.first, id = pr.second;
        if (id == pe) continue;
        if (!tin[v]) {
            dfsBridge(v, id);
            low[u] = min(low[u], low[v]);
            if (low[v] > tin[u]) {
                isBridge[id] = true;
            }
        } else {
            low[u] = min(low[u], tin[v]);
        }
    }
}

     



void dfsOrient(int u) {
    vis[u] = true;
    for (auto &pr : adj[u]) {
        int v = pr.first, id = pr.second;
        if (used_edge[id]) continue;
        used_edge[id] = true;
        // orient u -> v
        answer[id] = {u, v};
        if (!vis[v]) {
            dfsOrient(v);
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
        adj[a].emplace_back(b,i);
        adj[b].emplace_back(a,i);
    }
    // 1) Bridge‐find
    dfsBridge(1, -1);

    // 2) If any bridge, no strongly‐connected orientation exists
    for(int id = 0; id < m; id++){
        if(isBridge[id]){
            cout << 0 << "\n";
            return 0;
        }
    }

    // 3) Orient all edges
    dfsOrient(1);

    // 4) Output all m oriented edges
    //    in input order (edge IDs 0..m-1)
    for(int id = 0; id < m; id++){
        cout << answer[id].first
             << " " 
             << answer[id].second
             << "\n";
    }
    return 0;
}
