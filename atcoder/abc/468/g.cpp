#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<int> p(n + 1), inv(n + 1);

    for (int i = 1; i <= n; i++) {
        cin >> p[i];
        inv[p[i]] = i;
    }

    bool flipped = false;

    while (q--) {
        int t;
        cin >> t;

        if (t == 2) {
            flipped = !flipped;
        } else {
            int x, y;
            cin >> x >> y;

            if (!flipped) {
                int a = p[x], b = p[y];

                swap(p[x], p[y]);

                inv[a] = y;
                inv[b] = x;
            } else {
                int a = inv[x], b = inv[y];

                swap(inv[x], inv[y]);

                p[a] = y;
                p[b] = x;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << (flipped ? inv[i] : p[i]);
        cout << (i == n ? '\n' : ' ');
    }

    return 0;
} 


// wewemrosssotmi hsar mwer