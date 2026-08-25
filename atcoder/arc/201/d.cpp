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
        ll M;
        cin >> N >> M;

        vector<ll> A(N), B(N);

        for (ll &x : A) cin >> x;
        for (ll &x : B) cin >> x;

        // Convert (oldA + B) mod M
        // into (B - newA) mod M,
        // where newA = -oldA mod M.
        for (ll &x : A) {
            x = (M - x) % M;
        }

        sort(A.begin(), A.end());
        sort(B.begin(), B.end());

        // Duplicate B to unwrap the modulo circle.
        vector<ll> BB(2 * N);

        for (int i = 0; i < N; i++) {
            BB[i] = B[i];
            BB[i + N] = B[i] + M;
        }

        /*
            Find the smallest shift s such that

                BB[i + s] >= A[i]

            for every i.

            For each A[i], p is the first position in BB
            satisfying BB[p] >= A[i].

            Then we need:
                i + s >= p
            =>  s >= p - i

            Therefore:
                s = max(p - i).
        */

        int s = 0;
        int p = 0;

        for (int i = 0; i < N; i++) {
            while (p < 2 * N && BB[p] < A[i]) {
                p++;
            }

            s = max(s, p - i);
        }

        /*
            s is the first feasible cyclic shift.

            Now the modular costs are simply ordinary
            nonnegative differences.
        */
        ll ans = 0;

        for (int i = 0; i < N; i++) {
            ans = max(ans, BB[i + s] - A[i]);
        }

        cout << ans << '\n';
    }

    return 0;
}
    



// wewarss owjsf wer