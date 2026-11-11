
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> A(N);
    vector<ll> L(N + 1, 0), R(N + 1, 0);

    for (int i = 0; i < N; i++) {
        cin >> A[i];
        R[A[i]]++;
    }

    ll ans = 0;
    ll sum = 0; // sum of L[x] * R[x]

    for (int j = 0; j < N; j++) {
        int x = A[j];

        // Remove midpoint from the right side.
        R[x]--;
        sum -= L[x];

        // Count valid pairs around midpoint j.
        ans += sum - L[x] * R[x];

        // Move midpoint into the left side.
        sum += R[x];
        L[x]++;
    }

    cout << ans << '\n';

    return 0;
}
