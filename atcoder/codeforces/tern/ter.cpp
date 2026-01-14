#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Compute the total cost to make all a_i >= T and all b_j <= T
ll computeCost(const vector<ll>& A, const vector<ll>& prefixA,
               const vector<ll>& B, const vector<ll>& suffixB,
               ll T) {
    int n = A.size();
    int m = B.size();
    // number of a_i that are < T
    ll k = lower_bound(A.begin(), A.end(), T) - A.begin();
    // cost to raise those k elements up to T
    ll costA = k * T - prefixA[k];

    // first index in B of element > T
    ll p = upper_bound(B.begin(), B.end(), T) - B.begin();
    ll r = m - p;  // number of b_j > T
    // cost to lower those r elements down to T
    ll costB = suffixB[p] - r * T;

    return costA + costB;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<ll> A(n), B(m);
    for (int i = 0; i < n; i++) cin >> A[i];
    for (int j = 0; j < m; j++) cin >> B[j];

    sort(A.begin(), A.end());
    sort(B.begin(), B.end());

    // Build prefix sums for A
    vector<ll> prefixA(n + 1, 0);
    for (int i = 0; i < n; i++) {
        prefixA[i + 1] = prefixA[i] + A[i];
    }
    // Build suffix sums for B
    vector<ll> suffixB(m + 1, 0);
    for (int i = m - 1; i >= 0; i--) {
        suffixB[i] = suffixB[i + 1] + B[i];
    }


    // weakness is a small  rw
    ll lo = 0, hi = max(A.back(), B.back());
    while (lo < hi) {
        ll mid = lo + (hi - lo) / 2;
        // slope = cost(mid+1) - cost(mid)
        ll cntA = lower_bound(A.begin(), A.end(), mid) - A.begin();
        ll cntB = m - (upper_bound(B.begin(), B.end(), mid) - B.begin());
        ll slope = cntA - cntB;
        if (slope < 0)
            lo = mid + 1;
        else
            hi = mid;
    }
    ll bestT = lo;

    // Compute answer at bestT and possibly bestT-1
    ll answer = computeCost(A, prefixA, B, suffixB, bestT);
    if (bestT > 0) {
        answer = min(answer, computeCost(A, prefixA, B, suffixB, bestT - 1));
    }

    cout << answer << "\n";
    return 0;
}
