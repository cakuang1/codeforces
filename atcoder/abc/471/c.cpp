#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<ll> a(n);
    for (ll& x : a) cin >> x;
    sort(a.begin(), a.end());

    int r = lower_bound(a.begin(), a.end(), 0LL) - a.begin();
    int l = r - 1;

    ll pos = 0, ans = 0;

    while (l >= 0 || r < n) {
        bool takeLeft;

        if (l < 0) {
            takeLeft = false;
        } else if (r == n) {
            takeLeft = true;
        } else {
            takeLeft = abs(pos - a[l]) <= abs(pos - a[r]);
        }

        ll next;
        if (takeLeft) {
            next = a[l--];
        } else {
            next = a[r++];
        }

        ans += abs(next - pos);
        pos = next;
    }

    cout << ans << '\n';
}