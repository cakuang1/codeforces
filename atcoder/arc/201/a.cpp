#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;

        ll div1 = 0;
        ll div2 = 0;
        ll total = 0;

        for (int i = 0; i < N; i++) {
            ll A, B, C;
            cin >> A >> B >> C;

            div1 += min(A, B);
            div2 += min(B, C);
            total += min(B, A + C);
        }

        ll ans = min({
            div1,
            div2,
            total / 2
        });

        cout << ans << '\n';
    }

    return 0;
}