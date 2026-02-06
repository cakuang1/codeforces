#include <bits/stdc++.h>
#include <atcoder/math>

using namespace std;
using ll = long long;   // ← FIX IS HERE

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        ll N, M, A, B;
        cin >> N >> M >> A >> B;

        // floor_sum(n, m, a, b) = sum_{k=0..n-1} floor((a*k + b) / m)
        ll P = atcoder::floor_sum(N, M, A, B);
        ll Q = atcoder::floor_sum(N, M, A - 1, B - 1);

        ll ans = N - (P - Q);  // = N - P + Q
        cout << ans << "\n";
    }
    return 0;
}


// weisths owermkae e 