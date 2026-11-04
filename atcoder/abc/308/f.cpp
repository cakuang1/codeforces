
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<ll> p(n);
    for (auto &x : p) cin >> x;

    vector<ll> l(m), d(m);
    for (auto &x : l) cin >> x;
    for (auto &x : d) cin >> x;

    vector<pair<ll, ll>> coupons(m);

    for (int i = 0; i < m; i++) {
        coupons[i] = {l[i], d[i]};
    }

    sort(p.begin(), p.end());
    sort(coupons.begin(), coupons.end());

    priority_queue<ll> pq;

    ll ans = 0;
    int j = 0;

    for (ll price : p) {
        ans += price;

        while (j < m && coupons[j].first <= price) {
            pq.push(coupons[j].second);
            j++;
        }

        if (!pq.empty()) {
            ans -= pq.top();
            pq.pop();
        }
    }

    cout << ans << '\n';
}
 
// wwhw essm psofs ssf simspfl wrsd wriwr wer
//wetwhrwer wids eirwrw