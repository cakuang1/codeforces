#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while(T--){
        int n;
        cin >> n;
        vector<int> r(n+1), indegree(n+1, 0);
        for(int i = 1; i <= n; i++){
            cin >> r[i];
            indegree[r[i]]++;
        }
        // 1) Find all cycle‐nodes by repeatedly peeling off indegree‐0 leaves
        queue<int> q;
        vector<bool> inCycle(n+1, true);
        for(int i = 1; i <= n; i++){
            if(indegree[i] == 0){
                q.push(i);
                inCycle[i] = false;
            }
        }
        while(!q.empty()){
            int u = q.front(); q.pop();
            int v = r[u];
            if(!inCycle[v]) continue;      // already peeled
            indegree[v]--;
            if(indegree[v] == 0){
                inCycle[v] = false;
                q.push(v);
            }
        }

        // 2) Build reverse graph so we can BFS *outward* from cycle‐nodes
        vector<vector<int>> rev(n+1);
        for(int i = 1; i <= n; i++){
            rev[r[i]].push_back(i);
        }

        // 3) Multi‐source BFS from all cycle nodes to compute dist-to-cycle
        queue<int> bfs;
        vector<int> dist(n+1, -1);
        for(int i = 1; i <= n; i++){
            if(inCycle[i]){
                dist[i] = 0;
                bfs.push(i);
            }
        }
        int maxDist = 0;
        while(!bfs.empty()){
            int u = bfs.front(); bfs.pop();
            for(int v: rev[u]){
                if(dist[v] == -1){        // not yet visited
                    dist[v] = dist[u] + 1;
                    maxDist = max(maxDist, dist[v]);
                    bfs.push(v);
                }
            }
        }

        // 4) The first stable year is (maxDist + 2):
        //    – it takes (maxDist+1) years for all tree‐nodes to get pruned into cycles,
        //    – and then one more year for the state to “freeze” (S_t = S_{t-1}).
        cout << (maxDist + 2) << "\n";
    }
    return 0;


}

//
// wdoes hti wewowrk wew