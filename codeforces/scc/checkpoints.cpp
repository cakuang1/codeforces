#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MOD = 1000000007;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<ll> cost(n);
    for(int i = 0; i < n; i++){
        cin >> cost[i];
    }

    int m;
    cin >> m;
    vector<vector<int>> adj(n);
    for(int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        --u; --v;               // convert to 0-based
        adj[u].push_back(v);
    }

    // Tarjan’s SCC globals
    vector<int> disc(n, -1), low(n, 0);
    vector<bool> onstack(n, false);
    stack<int> st;
    int timer = 0;
    vector<vector<int>> sccs;

    // Tarjan’s DFS (recursive)
    function<void(int)> dfs = [&](int u) {
        disc[u] = low[u] = timer++;
        st.push(u);
        onstack[u] = true;

        for(int v : adj[u]){
            if(disc[v] == -1) {
                dfs(v);
                low[u] = min(low[u], low[v]);
            }
            else if(onstack[v]) {
                low[u] = min(low[u], disc[v]);
            }
        }

        // If u is root of an SCC, pop until u
        if(low[u] == disc[u]) {
            vector<int> comp;
            while(true) {
                int v = st.top(); st.pop();
                onstack[v] = false;
                comp.push_back(v);
                if(v == u) break;
            }
            sccs.push_back(move(comp));
        }
    };

    // Run Tarjan on every node
    for(int i = 0; i < n; i++){
        if(disc[i] == -1)
            dfs(i);
    }

    // Compute answer: sum of min-costs, and product of counts
    ll totalCost = 0;
    ll ways      = 1;
    for(auto &comp : sccs){
        ll mn = LLONG_MAX;
        ll cnt = 0;
        for(int u : comp){
            if(cost[u] < mn){
                mn = cost[u];
                cnt = 1;
            } else if(cost[u] == mn){
                cnt++;
            }
        }
        totalCost += mn;
        ways = ways * cnt % MOD;
    }
    // build the directed wgrpah wad then wmwhat 
    cout << totalCost << " " << ways << "\n";
    return 0;
}

