#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    ll K, X, Y;
    cin >> N >> M >> K;
    cin >> X >> Y;

    vector<ll> A(N), B(M);
    for (ll &a : A) cin >> a;
    for (ll &b : B) cin >> b;

    sort(A.begin(), A.end());
    sort(B.begin(), B.end());

    vector<ll> pref(N + 1, 0);
    for (int i = 0; i < N; ++i) {
        pref[i + 1] = pref[i] + A[i];
    }

    ll totalMoney = X + K * Y;
    ll drinkCost = 0;
    ll billsNeeded = 0;
    int answer = 0;

    for (int d = 0; d <= M; ++d) {
        if (d > 0) {
            drinkCost += B[d - 1];
            billsNeeded += (B[d - 1] + K - 1) / K;
        }

        if (billsNeeded > Y) break;

        // Buy drinks first; their change can be used for desserts.
        ll remainingMoney = totalMoney - drinkCost;

        int desserts = int(
            upper_bound(pref.begin(), pref.end(), remainingMoney)
            - pref.begin()
        ) - 1;

        answer = max(answer, d + desserts);
    }

    cout << answer << '\n';
    return 0;
}