#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// f(A, M, k) = sum_{x=0}^{M-1} min_i (x xor A[i]),
// assuming all A[i] < 2^k and M <= 2^k.
ll solve_rec(const vector<int> &A, ll M, int k) {
    if (k == 0 || M == 0 || A.empty()) return 0;

    vector<int> B[2];
    B[0].reserve(A.size());
    B[1].reserve(A.size());

    // Partition A into B[0], B[1] by the (k-1)-th bit.
    for (int x : A) {
        int b = (x >> (k - 1)) & 1;
        B[b].push_back(x & ~(1 << (k - 1)));
    }

    // warpw tiso werwer
    // werwhw ow odusglsthso hweriws
    ll mid = 1LL << (k - 1);

    // Case 1: full range M == 2^k
    if (M == (1LL << k)) {
        if (!B[0].empty() && !B[1].empty()) {
            // both sides non-empty
            return solve_rec(B[0], mid, k - 1)
                 + solve_rec(B[1], mid, k - 1);
        }
        return 2 * solve_rec(A, mid, k - 1) + mid * mid;
    }




    ll ans;
    if (!B[0].empty()) {
        ans = solve_rec(B[0], L, k - 1);
    } else {
        // all numbers have bit (k-1)=1 → forced XOR penalty mid
        ans = solve_rec(A, L, k - 1) + mid * L;
    }

    // Right part: x in [mid, M)
    if (M > mid) {
        ll R = M - mid;
        if (!B[1].empty()) {
            ans += solve_rec(B[1], R, k - 1);
        } else {
            // all numbers have bit (k-1)=0 → forced penalty mid
            ans += solve_rec(A, R, k - 1) + mid * R;
        }
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    ll M;
    cin >> N >> M;
    vector<int> A(N);
    for (int i = 0; i < N; ++i) cin >> A[i];

    // A[i] < 2^30 in this problem, so we start with k = 30
    cout << solve_rec(A, M, 30) << '\n';
    return 0;
}


/