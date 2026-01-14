#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> p(n+1), q(n+1);
    for(int i = 1; i <= n; i++){
        cin >> p[i];
    }

    vector<char> vis(n+1, false);
    unordered_map<int, vector<int>> waiting;
    waiting.reserve(1024);

    for(int i = 1; i <= n; i++){
        if(vis[i]) continue;
        // extract one cycle of p
        vector<int> cycle;
        int x = i;
        while(!vis[x]){
            vis[x] = true;
            cycle.push_back(x);
            x = p[x];
        }
        int m = cycle.size();
        if(m % 2 == 1){
            // odd-length: rotate by (m+1)/2
            int shift = (m + 1) / 2;
            for(int j = 0; j < m; j++){
                int from = cycle[j];
                int to   = cycle[(j + shift) % m];
                q[from] = to;
            }
        } else {
            // even-length: must pair with a waiting cycle of same length
            auto it = waiting.find(m);
            if(it == waiting.end()){
                // store for later pairing
                waiting[m] = move(cycle);
            } else {
                // pair cycle 'it->second' with this 'cycle'
                vector<int> &c2 = it->second;
                // define interleaved 2m-cycle: a_j -> b_j -> a_{j+1}
                for(int j = 0; j < m; j++){
                    int a = c2[j];
                    int b = cycle[j];
                    q[a] = b;
                    q[b] = c2[(j + 1) % m];
                }
                waiting.erase(it);
            }
        }
    }

    // if any even-length cycle was unpaired, impossible
    if(!waiting.empty()){
        cout << "-1\n";
        return 0;
    }

    // output q
    for(int i = 1; i <= n; i++){
        cout << q[i] << (i<n? ' ' : '\n');
    }
    return 0;
}
 