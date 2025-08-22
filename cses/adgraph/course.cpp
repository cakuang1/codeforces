#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> rev_adj(n+1);
    vector<int> outdeg(n+1, 0);

    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;      // a → b means a must come before b
        rev_adj[b].push_back(a);
        outdeg[a]++;        // a has one more edge “out”
    }

    // Max‐heap of current sinks (outdeg == 0)
    priority_queue<int> pq;
    for(int i = 1; i <= n; i++){
        if(outdeg[i] == 0) pq.push(i);
    }

    vector<int> order(n+1);
    // We'll fill order[pos] with the course at that position
    // pos goes from n down to 1
    int pos = n;
    while(!pq.empty()){
        int u = pq.top(); pq.pop();
        order[pos--] = u;
        // “Remove” u: every predecessor v no longer has u as an outgoing edge
        for(int v : rev_adj[u]){
            if(--outdeg[v] == 0){
                pq.push(v);
            }
        }
    }
    
    // detemrien w
    for(int i = 1; i <= n; i++){
        cout << order[i] << (i<n?' ':'\n');
    }
    return 0;
}
