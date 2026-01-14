#include <bits/stdc++.h>
using namespace std;

using int64 = long long;
static const int64 MOD = 998244353;

static inline int64 norm(int64 x) {
    x %= MOD;
    if (x < 0) x += MOD;
    return x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    vector<int64> A(N), B(M);
    for (auto &x : A) cin >> x;
    for (auto &x : B) cin >> x;

    sort(B.begin(), B.end());
    vector<__int128_t> pref(M + 1, 0);
    for (int i = 0; i < M; i++) pref[i + 1] = pref[i] + (__int128_t)B[i];

    int64 ans = 0;

    for (int i = 0; i < N; i++) {
        int64 a = A[i];
        int p = lower_bound(B.begin(), B.end(), a) - B.begin();

        __int128_t left  = (__int128_t)a * p - pref[p];
        __int128_t right = (pref[M] - pref[p]) - (__int128_t)a * (M - p);

        // reduce mod safely from int128
        int64 add = (int64)((left + right) % MOD);
        ans = norm(ans + add);
    }

    cout << ans << "\n";
    return 0;
}
