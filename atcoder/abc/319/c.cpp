
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, D;
    ll P;
    cin >> N >> D >> P;

    vector<ll> F(N);
    for (auto &x : F) cin >> x;

    sort(F.rbegin(), F.rend());

    ll ans = 0;

    for (int i = 0; i < N; i += D) {
        ll sum = 0;

        for (int j = i; j < min(N, i + D); j++) {
            sum += F[j];
        }

        ans += min(sum, P);
    }

    cout << ans << '\n';
}
