#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<ll> x(n);
        for (int i = 0; i < n; i++) {
            cin >> x[i];
        }

        // Pair each value with its original index, then sort by value
        vector<pair<ll,int>> v(n);
        for (int i = 0; i < n; i++) {
            v[i] = { x[i], i };
        }
        sort(v.begin(), v.end());

        // Build prefix sums of the sorted values
        vector<ll> pref(n+1, 0);
        for (int i = 0; i < n; i++) {
            pref[i+1] = pref[i] + v[i].first;
        }
        ll total = pref[n];

        // Compute answer for each sorted position
        // sum_j |v[i].first - v[j].first|
        //   = v[i].first * i   - pref[i]
        //   + (total - pref[i+1]) - v[i].first * (n - i - 1)
        // Then add +n for the “+1” per segment.
        vector<ll> ans(n);
        for (int i = 0; i < n; i++) {
            ll xi = v[i].first;
            ll left_cost  = xi * i - pref[i];
            ll right_cost = (total - pref[i+1]) - xi * (n - i - 1);
            ll sum_abs = left_cost + right_cost;
            ans[v[i].second] = sum_abs + n;
        }

        // Output in original order
        for (int i = 0; i < n; i++) {
            cout << ans[i] << (i+1<n ? ' ' : '\n');
        }
    }

    return 0;
}
