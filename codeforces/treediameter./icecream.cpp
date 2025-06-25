#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, K;
    cin >> n >> K;
    vector<vector<pair<int,int>>> adj(n+1);
    for(int i = 0; i < n-1; i++){
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }

    auto find_farthest = [&](int src, vector<ll>& dist, vector<int>* parent=nullptr){
        dist.assign(n+1, LLONG_MAX);
        if(parent) parent->assign(n+1, -1);
        dist[src] = 0;
        stack<int> st;
        st.push(src);
        while(!st.empty()){
            int u = st.top(); st.pop();
            for(auto [v,w]: adj[u]){
                if(dist[v] == LLONG_MAX){
                    dist[v] = dist[u] + w;
                    if(parent) (*parent)[v] = u;
                    st.push(v);
                }
            }
        }
        int best = src;
        for(int i=1;i<=n;i++){
            if(dist[i] > dist[best]) best = i;
        }
        return best;
    };

    // 1) find diameter endpoints A,B and parent2
    vector<ll> dist;
    int A = find_farthest(1, dist);
    vector<int> parent2;
    int B = find_farthest(A, dist, &parent2);

    // reconstruct diameter path D[0]=A ... D[d-1]=B
    vector<int> D;
    for(int v = B; v != -1; v = parent2[v])
        D.push_back(v);
    reverse(D.begin(), D.end());
    int d = D.size();

    // prefix distance Delta[i] from A = D[0] to D[i]
    vector<ll> Delta(d);
    Delta[0] = 0;
    for(int i=1;i<d;i++){
        // find weight of edge D[i-1]-D[i]
        for(auto [v,w]: adj[D[i-1]]){
            if(v == D[i]){ Delta[i] = Delta[i-1] + w; break; }
        }
    }

    // mark diameter nodes
    vector<bool> onDiam(n+1,false);
    for(int x: D) onDiam[x] = true;

    // 2) compute height[i] = max dist into side subtree of D[i]
    vector<ll> height(d, 0);
    vector<char> seen(n+1, 0);
    for(int i=0;i<d;i++){
        seen[D[i]] = 1;  // root of DFS
    }
    for(int i=0;i<d;i++){
        int u = D[i];
        // for each neighbor not on diameter, DFS its subtree
        for(auto [v,w]: adj[u]){
            if(onDiam[v]) continue;
            // iterative DFS from v
            stack<pair<int,ll>> st;
            st.emplace(v, w);
            seen[v] = 1;
            while(!st.empty()){
                auto [x, distx] = st.top(); st.pop();
                height[i] = max(height[i], distx);
                for(auto [y,wy]: adj[x]){
                    if(!seen[y]){
                        seen[y] = 1;
                        st.emplace(y, distx + wy);
                    }
                }
            }
        }
    }

    // 3) build P and S
    vector<ll> P(d), S(d);
    P[0] = height[0] - Delta[0];
    for(int i=1;i<d;i++){
        P[i] = max(P[i-1], height[i] - Delta[i]);
    }
    S[d-1] = height[d-1] + Delta[d-1];
    for(int i=d-2;i>=0;i--){
        S[i] = max(S[i+1], height[i] + Delta[i]);
    }

    // 4) slide segment [L..R] with length r = min(K, d)
    ll bestVal = LLONG_MAX;
    int bestL = 0, bestR = 0;
    int maxLen = min(K, d);
    for(int L = 0; L + maxLen - 1 < d; L++){
        int R = L + maxLen - 1;
        // left end
        ll leftEnd = Delta[L];
        // right end
        ll rightEnd = Delta[d-1] - Delta[R];
        // branch max
        int mid = (L + R) >> 1;
        ll branch1 = P[mid] + Delta[L];
        ll branch2 = (mid+1 <= R ? S[mid+1] - Delta[R] : LLONG_MIN);
        ll branchMax = max(branch1, branch2);
        ll cur = max({leftEnd, rightEnd, branchMax});
        if(cur < bestVal){
            bestVal = cur;
            bestL = L; bestR = R;
        }
    }

    int r = bestR - bestL + 1;
    cout << r << "\n";
    for(int i=bestL;i<=bestR;i++){
        cout << D[i] << (i<bestR?' ':'\n');
    }


    return 0;
}
