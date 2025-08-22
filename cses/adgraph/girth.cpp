#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n+1);
    for(int i = 0; i < m; i++){
        int a,b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    const int INF = n+1;
    int ans = INF;

    // BFS from each start s
    vector<int> dist(n+1), parent(n+1);
    queue<int> q;
    for(int s = 1; s <= n; s++){
        // Early exit if we already found a triangle
        if(ans == 3) break;

        // init
        fill(dist.begin(),  dist.end(),  -1);
        fill(parent.begin(), parent.end(), -1);
        while(!q.empty()) q.pop();

        dist[s] = 0;
        q.push(s);

        // standard BFS
        while(!q.empty()){
            int u = q.front(); 
            q.pop();
            // If u is so far from s that any new cycle would be >=ans, stop.
            if(dist[u] * 2 + 1 >= ans) continue;

            for(int v : g[u]){
                if(dist[v] == -1){
                    dist[v] = dist[u] + 1;
                    parent[v] = u;
                    q.push(v);
                }
                else if(parent[u] != v){
                    // found a cycle u→...→s and u—v plus v→...→s
                    int cycle_len = dist[u] + dist[v] + 1;
                    ans = min(ans, cycle_len);
                }
            }
        }
    }
    // detemienthe sohrots twpath w
    cout << (ans == INF ? -1 : ans) << "\n";
    return 0;
}
