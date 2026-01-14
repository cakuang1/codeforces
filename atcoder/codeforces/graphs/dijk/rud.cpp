#include <bits/stdc++.h>
using namespace std;
using ll = long long;
static const ll INF = LLONG_MAX / 4;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while(T--){
        int n, m;
        cin >> n >> m;
        string init;
        cin >> init;
        int start = 0;
        // build initial bitmask
        for(int i = 0; i < n; i++){
            if(init[i] == '1') start |= 1 << i;
        }

        struct Med { 
            int days;
            int rem_mask, add_mask;
        };
        vector<Med> meds(m);

        // read medicines
        for(int i = 0; i < m; i++){
            int d; 
            cin >> d;
            meds[i].days = d;

            string rem, add;
            cin >> rem >> add;
            int r = 0, a = 0;
            for(int j = 0; j < n; j++){
                if(rem[j]=='1') r |= 1 << j;
                if(add[j]=='1') a |= 1 << j;
            }
            meds[i].rem_mask = r;
            meds[i].add_mask = a;
        }

        int FULL = 1 << n;
        vector<ll> dist(FULL, INF);
        dist[start] = 0;
        // min-heap of (days, mask)
        priority_queue<pair<ll,int>,
                       vector<pair<ll,int>>,
                       greater<>> pq;
        pq.push({0, start});

        while(!pq.empty()){
            auto [cd, mask] = pq.top();
            pq.pop();
            if(cd > dist[mask]) continue;
            if(mask == 0) break;  // reached all‐clear

            // try each medicine
            for(auto &med : meds){
                int nm = (mask & ~med.rem_mask) | med.add_mask;
                ll nd = cd + med.days;
                if(nd < dist[nm]){
                    dist[nm] = nd;
                    pq.push({nd, nm});
                }
            }
        }
        
        

        ll ans = dist[0];
        if(ans >= INF/2) ans = -1;
        cout << ans << "\n";
    }
    return 0;
}
