#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;
    vector<ll> A(N+1);
    for (int i = 1; i <= N; i++) cin >> A[i];

    vector<ll> S0(N+1,0), S1(N+1,0), S2(N+1,0);
    for (int i = 1; i <= N; i++) {
        S0[i] = S0[i-1] + A[i];
        S1[i] = S1[i-1] + 1LL*i*A[i];
        S2[i] = S2[i-1] + 1LL*i*i*A[i];
    }

    while (Q--) {
        int L,R; cin >> L >> R;
        ll sumA = S0[R]-S0[L-1];
        ll sumJA = S1[R]-S1[L-1];
        ll sumJ2A = S2[R]-S2[L-1];

        ll ans = -sumJ2A + 1LL*(L+R)*sumJA + 1LL*(R+1)*(1LL - L)*sumA;
        cout << ans << "\n";
    }
    return 0;
}

