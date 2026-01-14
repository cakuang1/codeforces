#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int Q;
    cin >> Q;

    deque<pair<ll,ll>> dq; // (count, value)

    while (Q--) {
        int type;
        cin >> type;

        if (type == 1) {
            ll c, x;
            cin >> c >> x;
            dq.push_back({c, x});
        } else {
            ll k;
            cin >> k;

            ll res = 0;
            while (k > 0) {
                auto [c, x] = dq.front();
                dq.pop_front();

                ll take = min(c, k);
                res += take * x;
                k -= take;

                if (c > take) {
                    dq.push_front({c - take, x});
                }
            }
            cout << res << "\n";
        }
    }

    return 0;
}

//w e