
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> a(n), b(m);

    for (int &x : a) cin >> x;
    for (int &x : b) cin >> x;

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    auto check = [&](int x) {
        int sellers = upper_bound(a.begin(), a.end(), x) - a.begin();
        int buyers = b.end() - lower_bound(b.begin(), b.end(), x);

        return sellers >= buyers;
    };

    int l = 1, r = 1000000001;

    while (l < r) {
        int mid = l + (r - l) / 2;

        if (check(mid)) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }

    cout << l << '\n';

    return 0;
}
