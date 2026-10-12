#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, S;
    ll L;
    cin >> N >> S >> L;

    // pos[i] = distance from town 1 to town i
    vector<ll> pos(N + 1, 0);

    for (int i = 1; i < N; ++i) {
        ll a;
        cin >> a;
        pos[i + 1] = pos[i] + a;
    }

    int answer = 1;

    for (int l = 1; l <= S; ++l) {
        for (int r = S; r <= N; ++r) {
            ll x = pos[S] - pos[l];
            ll y = pos[r] - pos[S];

            ll cost = min(2 * x + y, x + 2 * y);

            if (cost <= L) {
                answer = max(answer, r - l + 1);
            }
        }
    }

    cout << answer << '\n';
}