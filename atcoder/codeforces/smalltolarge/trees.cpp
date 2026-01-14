#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 100005;
int n, q;
int col[MAXN];
vector<int> adj[MAXN];
map<int,int>*  mp[MAXN];
multiset<int>* cnts[MAXN];
vector<pair<int,int>> queries[MAXN];
int answer[MAXN];

void dfs(int u, int p){
    // 1) descend into children
    for(int v : adj[u]){
        if(v == p) continue;
        dfs(v, u);
    }
    // 2) init u’s data
    mp[u]   = new map<int,int>();
    cnts[u] = new multiset<int>();
    (*mp[u])[ col[u] ] = 1;
    cnts[u]->insert(1);
    
    // 3) small‐to‐large merge children into u
    for(int v : adj[u]){
        if(v == p) continue;

        // ensure u’s map is the larger one
        if(mp[v]->size() > mp[u]->size()){
            swap(mp[u], mp[v]);
            swap(cnts[u], cnts[v]);
        }

        // merge every (color→freq) from child v
        for(auto &pr : *mp[v]){
            int color = pr.first;
            int freq  = pr.second;

            int prev = (*mp[u])[color];
            // remove one copy of the old freq
            auto it = cnts[u]->find(prev);
            if(it != cnts[u]->end())
                cnts[u]->erase(it);

            int now = prev + freq;
            (*mp[u])[color] = now;
            cnts[u]->insert(now);
        }
        delete mp[v];
        mp[v] = nullptr;
        delete cnts[v];
        cnts[v] = nullptr;
    }


    for(auto &qr : queries[u]){
        int qi = qr.first;
        int k  = qr.second;
        // count how many subtree‐frequencies >= k
        auto it = cnts[u]->lower_bound(k);
        answer[qi] = distance(it, cnts[u]->end());
    }
}


//
int main(){ 
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    for(int i = 1; i <= n; i++){
        cin >> col[i];
    }
    for(int i = 1, u, v; i < n; i++){
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for(int i = 0, v, k; i < q; i++){
        cin >> v >> k;
        queries[v].emplace_back(i, k);
    } 
    dfs(1, 0);  
    
    
    for(int i = 0; i < q; i++){
        cout << answer[i] << "\n";
    } 
     we
        
     
    return 0;

} 
