
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    string s;
    cin >> s;

    ll res = 0;

    vector<ll> m(1 << 3, 0);
    vector<ll> me(1 << 3, 0);

    for (int i = 0; i < n; i++) {

        if (s[i] == 'M') {
            m[1 << a[i]]++;
        }
        else if (s[i] == 'E') {
            for (int j = 0; j < (1 << 3); j++) {
                if (m[j] != 0) {
                    me[j | (1 << a[i])] += m[j];
                }
            }
        }
        else {
            for (int j = 0; j < (1 << 3); j++) {
                if (me[j] == 0) continue;

                int seen = j | (1 << a[i]);

                int score = 3;
                for (int k = 0; k < 3; k++) {
                    if (!(seen & (1 << k))) {
                        score = k;
                        break;
                    }
                }

                res += 1LL * score * me[j];
            }
        }
    }

    cout << res << '\n';
    return 0;
}
