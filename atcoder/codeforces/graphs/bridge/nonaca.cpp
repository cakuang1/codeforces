#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int T; 
  cin >> T;
  while (T--) {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
      int a, b;
      cin >> a >> b;
      --a; --b;
      adj[a].push_back(b);
      adj[b].push_back(a);
    }

    // Total possible unordered pairs = n*(n-1)/2
    ll total_pairs = ll(n) * (n - 1) / 2;
    ll max_bridge_pairs = 0;

    // Tarjan arrays
    vector<int> disc(n, -1), low(n, 0), subtreesize(n, 0);
    int timer = 0;

    // We'll use an explicit stack of frames instead of recursion.
    struct Frame { int u, p, idx; };
    vector<Frame> st;
    st.reserve(n);

    for (int start = 0; start < n; start++) {
      if (disc[start] != -1) 
        continue;

      // push root frame
      st.push_back({start, -1, 0});

      while (!st.empty()) {
        Frame &f = st.back();
        int u = f.u, p = f.p, &i = f.idx;
            
        if (i == 0) {
          // first time we see u
          disc[u] = low[u] = timer++;rw
          subtreesize[u] = 1;
        }

        if (i < (int)adj[u].size()) {
          int v = adj[u][i++]; 
          if (v == p) {
            // ignore the edge back to parent
            continue;
          }
          if (disc[v] == -1) {
            // tree edge → recurse
            st.push_back({v, u, 0});
          } else {
            // back edge or cross edge
            low[u] = min(low[u], disc[v]);
          }
        } else {
          // all neighbors processed → "return" from u to p
          st.pop_back();
          if (p != -1) {
            // propagate low-link up
            low[p] = min(low[p], low[u]);

            // if (u,p) is a bridge:
            if (low[u] > disc[p]) {
              // removing this bridge splits the component into
              // sizes subtreesize[u]  and  (n - subtreesize[u])
              ll part = ll(n - subtreesize[u]) * subtreesize[u];
              max_bridge_pairs = max(max_bridge_pairs, part);
            }

            // accumulate subtree size
            subtreesize[p] += subtreesize[u];
          }
        }
      }
    }

    // subtract the worst‐case bridge split
    cout << (total_pairs - max_bridge_pairs) << "\n";
  }
  return 0;
}
