#include <bits/stdc++.h>
using namespace std;
using ll = long long;
static const ll INF = (ll)4e18;

struct State {
    ll time;
    int city, bike; 
    // we want a min‐heap, so reverse comparison
    bool operator<(State const& o) const {
        return time > o.time;
    }
};


void solve(){
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int,int>>> adj(n+1);
    for(int i = 0; i < m; i++){
        int u,v,w;
        cin >> u >> v >> w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
    vector<int> s(n+1);
    for(int i = 1; i <= n; i++){
        cin >> s[i];
    }
    // dist[city][bike_owner] = best time to reach `city` while riding bike bought at `bike_owner`
    static ll distArr[1001][1001]; // n<=1000
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            distArr[i][j] = INF;

    priority_queue<State> pq;
    // initial: must buy at city 1
    distArr[1][1] = 0;
    pq.push({0, 1, 1});
     
    while(!pq.empty()){
        auto st = pq.top(); 
        pq.pop();
        ll t = st.time;
        int u = st.city;
        int b = st.bike;
        if(t > distArr[u][b]) continue;

        // 1) try traveling along every edge (u->v) with bike b
        for(auto &ed : adj[u]){
            int v = ed.first;
            int w = ed.second;
            ll nt = t + (ll)w * s[b];
            if(nt < distArr[v][b]){
                distArr[v][b] = nt;
                pq.push({nt, v, b});
            }
        }

        // 2) try buying a new bike at city u
        //    (only do it if it's strictly faster, to avoid cycles)
        if(s[u] < s[b]){
            if(t < distArr[u][u]){
                distArr[u][u] = t;
                pq.push({t, u, u});
            }
        }
    }

    // answer = min over which bike you're on when you arrive at n
    ll ans = INF;
    for(int b = 1; b <= n; b++){
        ans = min(ans, distArr[n][b]);
    }
    cout << ans << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; 
    cin >> T;
    while(T--) solve();
    return 0;
}
