#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<pair<ll,int>> events;
    events.reserve(2*n);

    // Build sweep events: +1 at l, -1 at r+1
    for(int i = 0; i < n; i++){
        ll l, r;
        cin >> l >> r;
        events.emplace_back(l,   +1);
        events.emplace_back(r+1, -1);
    }
    // Sort by x-coordinate
    sort(events.begin(), events.end(),
         [](auto &A, auto &B){
             return A.first < B.first;
         });
        

    vector<ll> cnt(n+1, 0);
    ll curCover = 0;
    ll lastX    = events[0].first;
    int m = events.size(), i = 0;

    // Sweep through all event points
    while(i < m){
        ll x = events[i].first;
        // All integer points in [lastX, x) had coverage = curCover
        ll len = x - lastX;
        if(curCover > 0 && len > 0)
            cnt[curCover] += len;

        // Process all events at this same x
        while(i < m && events[i].first == x){
            curCover += events[i].second;
            i++;
        }
        lastX = x;
    }
    // wercoutnt the t wrnubmer of inversion  we we
    // Output cnt[1..n]
    for(int k = 1; k <= n; k++){
        cout << cnt[k] << (k == n ? '\n' : ' ');
    }
    return 0;
}
