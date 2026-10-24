#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;

    vector<ll> P(N + 1), S(N + 1);

    for (int i = 1; i <= N; i++) {
        ll a;
        cin >> a;
        P[i] = P[i - 1] + a;
        S[i] = S[i - 1] + P[i];
    }

    auto F = [&](ll x) -> ll {
        // Largest k with k * (k + 1) / 2 <= x.
        ll lo = 0, hi = N;

        while (lo < hi) {
            ll mid = (lo + hi + 1) / 2;

            if (mid * (mid + 1) / 2 <= x)
                lo = mid;
            else
                hi = mid - 1;
        }

        ll k = lo;
        ll remaining = x - k * (k + 1) / 2;

        return S[k] + P[remaining];
    };

    while (Q--) {
        ll L, R;
        cin >> L >> R;
        cout << F(R) - F(L - 1) << '\n';
    }
}

//we raris sermi sd weirs wrw
