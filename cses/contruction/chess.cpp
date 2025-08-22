#include <bits/stdc++.h>
using namespace std;
using pii = pair<int,int>;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<long long> x(n+1);
    long long sum = 0;
    for(int i = 1; i <= n; i++){
        cin >> x[i];
        if(x[i] < 0 || x[i] > n-1){
            cout << "IMPOSSIBLE\n";
            return 0;
        }
        sum += x[i];
    }
    // Sum of degrees must be even
    if(sum % 2){
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    // Max‐heap of (remaining_degree, node)
    priority_queue<pii> pq;
    for(int i = 1; i <= n; i++){
        if(x[i] > 0) pq.push({x[i], i});
    }

    vector<pii> edges;
    edges.reserve(sum/2);

    while(!pq.empty()){
        auto [d,u] = pq.top(); pq.pop();
        if(d > (int)pq.size()){
            // Not enough other vertices to satisfy u’s degree
            cout << "IMPOSSIBLE\n";
            return 0;
        }
        // Take the next d highest‐degree vertices
        vector<pii> buf;
        buf.reserve(d);
        for(int k = 0; k < d; k++){
            auto top = pq.top(); pq.pop();
            buf.push_back(top);
        }
        // Connect u to each of them
        for(auto &pr : buf){
            int v = pr.second;
            edges.emplace_back(u, v);
        }
        // Decrement their degrees and push back if still >0
        for(auto &pr : buf){
            int deg = pr.first - 1;
            int v   = pr.second;
            if(deg < 0){
                cout << "IMPOSSIBLE\n";
                return 0;
            }
            if(deg > 0) pq.push({deg, v});
        }
    }

    // Success
    cout << edges.size() << "\n";
    for(auto &e : edges){
        cout << e.first << " " << e.second << "\n";
    }
    return 0;
}
