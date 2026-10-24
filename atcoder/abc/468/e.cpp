#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll MOD = 998244353;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<ll> pref(N + 1, 0);
    for (int i = 1; i <= N; ++i) {
        ll a;
        cin >> a;
        pref[i] = (pref[i - 1] + a) % MOD;
    }

    vector<ll> inv(N + 1), H(N + 1, 0);
    inv[1] = 1;

    for (int i = 2; i <= N; ++i) {
        inv[i] = MOD - (MOD / i) * inv[MOD % i] % MOD;
    }

    for (int i = 1; i <= N; ++i) {
        H[i] = (H[i - 1] + inv[i]) % MOD;
    }

    ll answer = 0;

    for (int i = 1; i <= N; ++i) {
        ll coefficient = (H[i] - H[N - i] + MOD) % MOD;
        answer = (answer + pref[i] * coefficient) % MOD;
    }

    cout << answer << '\n';
    return 0;
}