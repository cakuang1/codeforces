#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    // Build adjacency list
    vector<vector<int>> adj(n+1);
    for(int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Iterative DFS to produce the Euler‐tour of the spanning tree
    vector<bool> seen(n+1,false);
    vector<int> euler;
    euler.reserve(2*n);

    // stack entries: (node, next child index)
    vector<pair<int,int>> st;
    st.reserve(n);
    st.emplace_back(1, 0);
    seen[1] = true;

    while(!st.empty()){
        auto &top = st.back();
        int u = top.first;
        int &ci = top.second;
        if(ci == 0){
            // first time visiting u
            euler.push_back(u);
        }
        if(ci < (int)adj[u].size()){
            int v = adj[u][ci++];
            if(!seen[v]){
                seen[v] = true;
                st.emplace_back(v, 0);
            }
        } else {
            // finished all children of u
            euler.push_back(u);
            st.pop_back();
        }
    }

    // We have at most 2n-1 entries
    int S = (int)euler.size();
    // ceil( S / k )
    int limit = (S + k - 1) / k;

    // Now print exactly k routes
    int p = 0;
    for(int i = 0; i < k; i++){
        if(p < S){
            int sz = min(limit, S - p);
            cout << sz;
            for(int j = 0; j < sz; j++, p++){
                cout << ' ' << euler[p];
            }
            cout << "\n";
        } else {
            // No more real entries: trivial route at node 1
            cout << "1 1\n";
        }
    }
    return 0;
}

