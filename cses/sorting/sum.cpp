#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; ll x;
    cin >> n >> x;
    vector<ll> a(n+1);
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }

    // mp[s] = some pair (i,j) with a[i]+a[j] == s
    unordered_map<ll, pair<int,int>> mp;
    mp.reserve(n*(n-1)/2);            // avoid rehashing
    mp.max_load_factor(0.25f);

    for(int i = 1; i <= n; i++){
        for(int j = i+1; j <= n; j++){
            ll s = a[i] + a[j];
            ll need = x - s;
            auto it = mp.find(need);
            if(it != mp.end()){
                int u = it->second.first;
                int v = it->second.second;
                // make sure all four indices are distinct
                if(u!=i && u!=j && v!=i && v!=j){
                    cout << u << ' ' << v << ' '
                         << i << ' ' << j << "\n";
                    return 0;
                }
            }
            // only store the first pair yielding sum s
            if(mp.find(s) == mp.end()){
                mp[s] = {i,j};
            }
        }
    }

    cout << "IMPOSSIBLE\n";
    return 0;
}
