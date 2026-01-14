#include <bits/stdc++.h>
using namespace std;
#define int long long
#define INF (int)1e18
#define f first
#define s second

mt19937_64 RNG(chrono::steady_clock::now().time_since_epoch().count());

void Solve() 
{
    int n;
    cin >> n;
    
    vector<vector<int>> E(n);
    
    for (int i = 1; i < n; i++){
        int u, v; cin >> u >> v;
        
        u--; v--;
        E[u].push_back(v);
        E[v].push_back(u);
    }
    
    auto bfs = [&](int s){
      vector<int> d(n, -1);
      d[s] = 0;
      queue<int> Q;
      Q.push(s);
      while (!Q.empty()){
        int v = Q.front();
        Q.pop();
        for (int w : E[v]){
          if (d[w] == -1){
            d[w] = d[v] + 1;
            Q.push(w);
          }
        }
      }
      return d;
    };
    
    vector<int> d1 = bfs(0);
    int a = max_element(d1.begin(), d1.end()) - d1.begin();
    vector<int> d2 = bfs(a);
    int b = max_element(d2.begin(), d2.end()) - d2.begin();
    vector<int> d3 = bfs(b);
    int diam = d3[max_element(d3.begin(), d3.end()) - d3.begin()] + 1;
    //if 3 we want 1, 1 if 4 we want 1 2 
    
    vector <int> ans;
    for (int i = 0; i < n; i++){
        if ((d2[i] + d3[i] == diam - 1) && ((d2[i] == diam/2) || (d3[i] == diam/2))) 
            ans.push_back(i);
    }
    
    if (diam & 1) assert(ans.size() == 1);
    else assert(ans.size() == 2);
    
    vector <pair<int, int>> ok;
    
    if (diam & 1){
        //print everything from 0 to diam/2 
        for (int i = 0; i <= diam/2; i++){
            ok.push_back({ans[0], i});
        }
    } else {
        //2 => 2 ops, 4 => 2 ops , 6 => 4 ops, 8 => 4 ops 
        int ops = ((n - 2)/4) + 1;
        int need = (diam/2) - 1;
        while (need >= 0){
            ok.push_back({ans[0], need});
            ok.push_back({ans[1], need});
            
            need -= 2;
        }
    }
    
    cout << ok.size() << "\n";
    for (auto [u, r] : ok){
        cout << u + 1 << " " << r << "\n";
    }
} 

int32_t main() 
{ 
    auto begin = std::chrono::high_resolution_clock::now();
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    cin >> t;
    for(int i = 1; i <= t; i++) 
    {
        //cout << "Case #" << i << ": ";
        Solve();
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
   // cerr << "Time measured: " << elapsed.count() * 1e-9 << " seconds.\n"; 
    return 0;
}