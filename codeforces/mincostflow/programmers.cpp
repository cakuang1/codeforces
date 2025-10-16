#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, b, n;
    cin >> a >> b >> n;
    vector<pair<long long, long long>> v(n);
    for (auto &p : v) cin >> p.first >> p.second; // x, y

    vector<long long> diff;
    diff.reserve(n);
    for (int i = 0; i < n; ++i)
        diff.push_back(v[i].first - v[i].second);

    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](int i, int j) {
        return (v[i].first - v[i].second) > (v[j].first - v[j].second);
    });

    long long ans = 0;
    // first a as programmers
    for (int i = 0; i < a; ++i)
        ans += v[idx[i]].first;

    // last b as artists
    for (int i = n - b; i < n; ++i)
        ans += v[idx[i]].second;

    cout << ans << "\n";
    return 0;
}


// w wedsothesi erwowkradn erwho dyou so osethsi wr
// wcncoes wra rw what wera=d nwer hwo dyo uosvlsehti we

// wconnecstwit hwetthe trick wris what ew

// wlkaiern weprospr imzonit ewr

//  lienr rprogramginw rwmeans what 

