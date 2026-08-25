#include <bits/stdc++.h>
#include <atcoder/segtree>
using namespace std;
using namespace atcoder;

using ll = long long;

ll op(ll a, ll b) {
    return max(a, b);
}

ll e() {
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<ll> A(N);
    for (ll &x : A) cin >> x;

    // Prefix sums:
    // sum of A[l...r] = pref[r+1] - pref[l]
    vector<ll> pref(N + 1);
    for (int i = 0; i < N; ++i) {
        pref[i + 1] = pref[i] + A[i];
    }

    // Segment tree stores maximum A[i].
    segtree<ll, op, e> seg(A);

    vector<ll> ans(N);

    for (int K = 0; K < N; ++K) {
        int L = K;
        int R = K;

        ll S = A[K];

        while (true) {
            // We want to move through all values < S.
            auto smaller = [&](ll mx) {
                return mx < S;
            };

            /*
             * LEFT SIDE
             *
             * min_left(L, smaller) finds the smallest x such that
             *
             *   max(A[x ... L-1]) < S
             *
             * Therefore:
             *
             *   x-1 = nearest position to the left with A[x-1] >= S
             *
             * and everything x ... L-1 can be eaten.
             */
            int newL = seg.min_left(L, smaller);

            /*
             * RIGHT SIDE
             *
             * max_right(R+1, smaller) finds the first position x where
             * A[x] >= S.
             *
             * Therefore everything R+1 ... x-1 can be eaten.
             */
            int blockerRight = seg.max_right(R + 1, smaller);
            int newR = blockerRight - 1;

            // Nothing new can be eaten.
            if (newL == L && newR == R) {
                break;
            }

            L = newL;
            R = newR;

            // Takahashi has absorbed the whole interval.
            S = pref[R + 1] - pref[L];
        }

        ans[K] = S;
    }

    for (int i = 0; i < N; ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
}