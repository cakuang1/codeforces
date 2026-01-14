#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n+1);
    for(int i = 2; i <= n; i++){
        int p;
        cin >> p;
        adj[p].push_back(i);
        adj[i].push_back(p);
    }

    string s;
    cin >> s;  // s[0] is color of node 1
    vector<int> ch(n+1);
    for(int i = 1; i <= n; i++){
        ch[i] = s[i-1] - 'a';
    }

    vector<int> parent(n+1, 0), depth(n+1, 0);
    vector<int> tin(n+1), tout(n+1);
    int timer = 1, maxd = 1;

    // We'll collect, for each depth d, the list of tin[] and the list of letter‐bitmasks
    vector<vector<int>> depth_tins(n+1), depth_masks(n+1);

    // iterative DFS to avoid recursion overflow
    vector<int> st, it;
    st.reserve(n);
    it.reserve(n);

    st.push_back(1);
    it.push_back(0);
    parent[1] = 0;
    depth[1] = 1;

    while(!st.empty()){
        int u = st.back();
        int &i = it.back();
        if(i == 0){
            // pre‐visit
            tin[u] = timer++;
            int d = depth[u];
            maxd = max(maxd, d);
            depth_tins[d].push_back(tin[u]);
            depth_masks[d].push_back(1 << ch[u]);
        }
        if(i < (int)adj[u].size()){
            int v = adj[u][i++];
            if(v == parent[u]) continue;
            parent[v] = u;
            depth[v] = depth[u] + 1;
            st.push_back(v);
            it.push_back(0);
        } else {
            // post‐visit
            tout[u] = timer;
            st.pop_back();
            it.pop_back();
        }
    }

    // build prefix‐xor for each depth
    vector<vector<int>> pref_xor(n+1);
    for(int d = 1; d <= maxd; d++){
        int L = depth_tins[d].size();
        auto &masks = depth_masks[d];
        auto &px = pref_xor[d];
        px.assign(L+1, 0);
        for(int i = 0; i < L; i++){
            px[i+1] = px[i] ^ masks[i];
        }
    }

    // answer queries
    while(m--){
        int v, h;
        cin >> v >> h;
        if(h > maxd){
            cout << "Yes\n";
            continue;
        }
        auto &tins = depth_tins[h];
        if(tins.empty()){
            cout << "Yes\n";
            continue;
        }
        int in = tin[v], out = tout[v] - 1;
        // find first idx with tins[idx] >= in
        auto itL = lower_bound(tins.begin(), tins.end(), in);
        // find first idx with tins[idx] > out
        auto itR = upper_bound(tins.begin(), tins.end(), out);
        int L = int(itL - tins.begin());
        int R = int(itR - tins.begin()) - 1;
        if(L > R){
            // no nodes in v's subtree at depth h
            cout << "Yes\n";
            continue;
        }
        int mask = pref_xor[h][R+1] ^ pref_xor[h][L];
        // at most one bit set?
        if((mask & (mask-1)) == 0){
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }

    return 0;
}


