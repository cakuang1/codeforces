#include <bits/stdc++.h>
using namespace std;
using ll = long long;
static const ll INF = LLONG_MAX/4;

struct State {
    ll t;
    int u;
    int onHorse; // 0 = on foot, 1 = riding
    bool operator<(State const& o) const {
        // min‐heap
        return t > o.t;
    }
};

vector<ll> dijkstra(int n,
                    vector<vector<pair<int,int>>>& adj,
                    vector<bool>& hasHorse,
                    int start) {
    // dist[u][h] = best time to reach u with h∈{0,1}
    vector<array<ll,2>> dist(n+1, {INF, INF});
    priority_queue<State> pq;

    int initState = hasHorse[start] ? 1 : 0;
    dist[start][initState] = 0;
    pq.push({0, start, initState});

    while(!pq.empty()) {
        auto st = pq.top(); pq.pop();
        ll t = st.t;
        int u = st.u, h = st.onHorse;
        if (t > dist[u][h]) continue;

        // 1) mount a horse here if available and not already riding
        if (h == 0 && hasHorse[u]) {
            if (t < dist[u][1]) {
                dist[u][1] = t;
                pq.push({t, u, 1});
            }
        }

        // 2) travel each edge
        for (auto &ed : adj[u]) {
            int v = ed.first, w = ed.second;
            // time is w/2 if riding, else w
            ll nt = t + (h ? (w >> 1) : w);
            if (nt < dist[v][h]) {
                dist[v][h] = nt;
                pq.push({nt, v, h});
            }
        }
    }

    // return best time at each u (min of riding or not)
    vector<ll> best(n+1, INF);
    for (int u = 1; u <= n; u++) {
        best[u] = min(dist[u][0], dist[u][1]);
    }
    return best;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while(T--) {
        int n, m, h;
        cin >> n >> m >> h;
        vector<bool> hasHorse(n+1, false);
        for(int i = 0; i < h; i++){
            int x; 
            cin >> x;
            hasHorse[x] = true;
        }

        vector<vector<pair<int,int>>> adj(n+1);
        for(int i = 0; i < m; i++){
            int u, v, w;
            cin >> u >> v >> w;
            // w is even, per statement
            adj[u].emplace_back(v, w);
            adj[v].emplace_back(u, w);
        }
        
        
        auto distM = dijkstra(n, adj, hasHorse, 1);
        // run from Robin at n
        auto distR = dijkstra(n, adj, hasHorse, n);

        ll answer = INF;
        for(int u = 1; u <= n; u++){
            // they can wait, so meeting time is max of arrival times
            if(distM[u] < INF && distR[u] < INF){
                answer = min(answer, max(distM[u], distR[u]));
            }
        }

        if(answer == INF) cout << "-1\n";
        else              cout << answer << "\n";
    }
    return 0;
}
