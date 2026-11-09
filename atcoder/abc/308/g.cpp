
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> q;

    multiset<int> s, xr;

    auto eraseXor = [&](int x) {
        xr.erase(xr.find(x));
    };


    while (q--) {
        int t;
        cin >> t;

        if (t == 1) {
            int x;
            cin >> x;

            auto r = s.lower_bound(x);
            auto l = (r == s.begin() ? s.end() : prev(r));

            // Remove old adjacency
            if (l != s.end() && r != s.end()) {
                eraseXor(*l ^ *r);
            }

            // Add new adjacencies
            if (l != s.end()) {
                xr.insert(*l ^ x);
            }
            if (r != s.end()) {
                xr.insert(x ^ *r);
            }

            s.insert(x);
        }
        else if (t == 2) {
            int x;
            cin >> x;

            auto it = s.find(x);
            auto r = next(it);
            auto l = (it == s.begin() ? s.end() : prev(it));

            // Remove adjacencies involving x
            if (l != s.end()) {
                eraseXor(*l ^ x);
            }
            if (r != s.end()) {
                eraseXor(x ^ *r);
            }

            // Restore adjacency between neighbors
            if (l != s.end() && r != s.end()) {
                xr.insert(*l ^ *r);
            }

            s.erase(it);
        }
        else {
            cout << *xr.begin() << '\n';
        }
    }

    return 0;
}
