#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> a(n+1), pos(n+1);
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        pos[a[i]] = i;
    }

    // Initial round‐count: 1 + # of i where pos[i] > pos[i+1]
    int rounds = 1;
    for(int v = 1; v < n; v++){
        if(pos[v] > pos[v+1]) 
            ++rounds;
    }

    // Process each swap
    while(m--){
        int l, r;
        cin >> l >> r;
        int x = a[l], y = a[r];

        // Collect the at‐most‐4 adjacent‐by‐value pairs that might change
        set<pair<int,int>> upd;
        auto mark = [&](int u,int v){
            if(u >= 1 && u < v && v <= n)
                upd.insert({u,v});
        };
        mark(x,   x+1);
        mark(x-1, x);
        mark(y,   y+1);
        mark(y-1, y);

        // Subtract old contributions
        for(auto &pr : upd){
            if(pos[pr.first] > pos[pr.second]) 
                --rounds;
        }

        // Do the swap in the array and update positions
        swap(a[l], a[r]);
        pos[x] = r;
        pos[y] = l;

        // Add new contributions
        for(auto &pr : upd){
            if(pos[pr.first] > pos[pr.second]) 
                ++rounds;
        }

        cout << rounds << "\n";
    }

    return 0;
}
