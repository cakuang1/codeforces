#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll k; // Global game-day length; used in compute_f.

/// Computes the earliest time >= x that is congruent to h modulo k.
/// That is, f(x, h) = x - (x % k) + h if (x % k) <= h, else x - (x % k) + k + h.
ll compute_f(ll x, int h) {
    ll mod = x % k;
    if (mod <= h)
        return x - mod + h;
    else
        return x - mod + k + h;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    while(t--){
        int n, m;
        cin >> n >> m >> k;
        vector<int> h(n+1);
        for (int i = 1; i <= n; i++){
            cin >> h[i];
        }
        
        // Build the dependency graph.
        // adj: forward edges, rev: reverse edges.
        vector<vector<int>> adj(n+1), rev(n+1);
        vector<int> indeg(n+1, 0);
        for (int i = 0; i < m; i++){
            int a, b;
            cin >> a >> b;
            adj[a].push_back(b);
            rev[b].push_back(a);
            indeg[b]++;
        }
        
        // --- Step 1. Compute base completion times for x = 0.
        // For a vertex with no prerequisites, c[v] = f(0, h[v]) = h[v] (since 0 mod k = 0).
        vector<ll> c(n+1, 0);
        // We'll use a copy of indeg for the topological sort.
        vector<int> in = indeg;
        queue<int> q;
        for (int v = 1; v <= n; v++){
            if (in[v] == 0) {
                c[v] = h[v]; 
                q.push(v);
            }
        }
        
        // For vertices with dependencies, we need the maximum among the completion times of its prerequisites.
        vector<ll> parentMax(n+1, 0);
        vector<int> topo;
        while(!q.empty()){
            int v = q.front();
            q.pop();
            topo.push_back(v);
            for (int nx: adj[v]){
                parentMax[nx] = max(parentMax[nx], c[v]);
                in[nx]--;
                if (in[nx] == 0) {
                    c[nx] = compute_f(parentMax[nx], h[nx]);
                    q.push(nx);
                }
            }
        }
        
        // Compute the overall maximum completion time.
        ll global_max = 0;
        for (int v = 1; v <= n; v++){
            global_max = max(global_max, c[v]);
        }
        
        // The answer candidate if we start at x = 0.
        ll best = global_max - 0;
        
        // --- Step 2. Prepare the event list.
        // Only vertices with no incoming dependencies (indegree zero) can be the first quest.
        // Their event time is just their h value.
        vector<pair<int,int>> events;
        for (int v = 1; v <= n; v++){
            if (indeg[v] == 0) { 
                events.push_back({h[v], v});
            }
        }
        sort(events.begin(), events.end());
        
        // --- Step 3. Process events: simulate increasing x only when an event occurs.
        // We'll define a DFS to update dependent vertices when a vertex's c value is increased.
        function<void(int)> dfs = [&](int v) {
            for (int nx : adj[v]){
                ll old = c[nx];
                // Recompute parent's maximum for nx by checking all its prerequisites.
                ll new_parent = 0;
                for (int p : rev[nx]){
                    new_parent = max(new_parent, c[p]);
                }
                ll new_val = compute_f(new_parent, h[nx]);
                if(new_val > c[nx]){
                    c[nx] = new_val;
                    global_max = max(global_max, c[nx]);
                    dfs(nx);
                }
            }
        };
        
        int current_x = 0;
        // Process events in increasing order.
        for (auto &e: events){
            int event_x = e.first; // the event's x value (a scheduled hour for an indegree-zero quest)
            current_x = event_x;
            int v = e.second;
            // When x reaches event_x, quest v must be performed in the next day.
            // That means its c[v] increases by k.
            c[v] += k;
            global_max = max(global_max, c[v]);
            // Propagate this update to all quests depending on v.
            dfs(v);
            
            // Update candidate answer: overall span = global_max - current starting time.
            best = min(best, global_max - (ll)current_x);
        }
        
        cout << best << "\n";
    }
    return 0;
}
