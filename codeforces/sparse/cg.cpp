#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<ll> a(n);
    for(int i = 0; i < n; i++)
        cin >> a[i];

    // ans[g] = total # of subarrays whose GCD = g
    unordered_map<ll,ll> ans;
    ans.reserve(n * 2);
     
    // 
    // cur holds pairs (g, nt) for subarrays ending at previous index
    vector<pair<ll,ll>> cur, nxt;

    for(int i = 0; i < n; i++){
        nxt.clear();

        // 1) extend all previous subarrays by a[i]
        for(auto &p : cur){
            ll g = std::gcd(p.first, a[i]);
            nxt.emplace_back(g, p.second);
        }
        // 2) the new subarray [i..i]
        nxt.emplace_back(a[i], 1LL);

        // 3) merge same-gcd entries in nxt
        sort(nxt.begin(), nxt.end(),
             [](auto &x, auto &y){ return x.first < y.first; });
        cur.clear();
        for(auto &p : nxt){
            if(!cur.empty() && cur.back().first == p.first)
                cur.back().second += p.second;
            else
                cur.push_back(p);
        }

        // 4) accumulate into global ans[]
        for(auto &p : cur){
            ans[p.first] += p.second;
        }
    }
    
    // gcd old always divides 
    int q;
    cin >> q;
    while(q--){
        ll x;
        cin >> x;
        auto it = ans.find(x);
        cout << (it == ans.end() ? 0LL : it->second) << "\n";
    }

    return 0;
}
