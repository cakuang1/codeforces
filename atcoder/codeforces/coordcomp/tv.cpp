#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<pair<ll,ll>> seg(n);
    vector<ll> coords;
    coords.reserve(2*n);

    for(int i = 0; i < n; i++){
        ll l, r;
        cin >> l >> r;
        seg[i] = {l, r};
        coords.push_back(l);
        coords.push_back(r + 1);
    }

    // Coordinate‐compress
    sort(coords.begin(), coords.end());
    coords.erase(unique(coords.begin(), coords.end()), coords.end());
    int K = coords.size();

    // Build diff array
    vector<ll> diff(K+1, 0);
    for(auto &p : seg){
        ll l = p.first, r = p.second;
        int Li = int(lower_bound(coords.begin(), coords.end(), l) - coords.begin());
        int Ri = int(lower_bound(coords.begin(), coords.end(), r+1) - coords.begin());
        diff[Li] += 1;
        diff[Ri] -= 1;
    }

    // Prefix‐sum to get cover count at each compressed index
    vector<ll> cover(K, 0);
    cover[0] = diff[0];
    for(int i = 1; i < K; i++){
        cover[i] = cover[i-1] + diff[i];
    }

    // Compute the length (number of integer points) in each span
    vector<ll> delta(K, 0);
    for(int i = 0; i+1 < K; i++){
        delta[i] = coords[i+1] - coords[i];
    }

    // Build prefix of “covered exactly once” counts
    // pref[i] = total # of integer points in spans [0..i-1] with cover==1
    vector<ll> pref(K+1, 0);
    for(int i = 0; i < K; i++){
        pref[i+1] = pref[i] + (cover[i]==1 ? delta[i] : 0);
    }

    // Find any redundant segment
    for(int i = 0; i < n; i++){
        ll l = seg[i].first, r = seg[i].second;
        int Li = int(lower_bound(coords.begin(), coords.end(), l) - coords.begin());
        int Ri = int(lower_bound(coords.begin(), coords.end(), r+1) - coords.begin());
        // number of points in [l..r] covered exactly once
        ll exactlyOne = pref[Ri] - pref[Li];
        if(exactlyOne == 0){
            cout << (i+1) << "\n";
            return 0;
        }
    }

    cout << -1 << "\n";
    return 0;
}

w