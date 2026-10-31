#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    ll d;
    cin >> n >> m >> d;

    vector<ll> a(n), b(m);

    for (auto &x : a) cin >> x;
    for (auto &x : b) cin >> x;

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    int i = n - 1;
    int j = m - 1;

    while (i >= 0 && j >= 0) {
        if (abs(a[i] - b[j]) <= d) {
            cout << a[i] + b[j] << '\n';
            return 0;
        }

        if (a[i] > b[j]) {
            i--;
        } else {
            j--;
        }
    }

    cout << -1 << '\n';
}