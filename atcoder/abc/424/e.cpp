#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Given one stick of length A, how many operations are required
// to make all pieces <= D?
ll ops_needed_one(ll A, long double D) {
    // Find smallest k such that A / 2^k <= D
    int k = 0;
    while ((long double)A / (1LL << k) > D) k++;
    // total splits = 2^k - 1
    return (1LL << k) - 1;
}

// Given all sticks, how many operations are required to make all <= D?
ll ops_needed_all(const vector<ll>& A, long double D) {
    ll total = 0;
    for (ll x : A) total += ops_needed_one(x, D);
    return total;
}

void solve() {
    int N; ll K, X;
    cin >> N >> K >> X;
    vector<ll> A(N);
    for (int i = 0; i < N; i++) cin >> A[i];

    // Binary search for threshold D
    long double lo = 0, hi = *max_element(A.begin(), A.end());
    for (int it = 0; it < 100; it++) {
        long double mid = (lo + hi) / 2;
        if (ops_needed_all(A, mid) <= K) hi = mid;
        else lo = mid;
    }
    long double D = hi; // smallest length threshold

    // Now reconstruct frequencies of lengths after K ops
    // We'll use a map<long double, long long> because lengths are exact dyadic rationals.
    map<long double, ll, greater<long double>> freq;

    for (ll a : A) {
        // split stick until all pieces <= D, but stop early if out of operations
        int k = 0;
        while ((long double)a / (1LL << k) > D) k++;
        long double final_len = (long double)a / (1LL << k);
        ll pieces = (1LL << k);
        freq[final_len] += pieces;
    }

    // But we might not have used exactly K operations; if we used fewer,
    // we can further split some sticks of length D (all equal length).
    ll used = ops_needed_all(A, D);
    ll remaining = K - used;

    if (remaining > 0) {
        // repeatedly split the largest available length > 0
        // All will be exactly length D, so we just add more of (D/2).
        // For safety, handle it:
        ll add = remaining;
        // Splitting one stick of length D produces 2 of D/2
        // So after "add" operations we add "add" more sticks (since count increases by 1 each op)
        freq[D] -= add; // we split some D’s
        freq[D/2] += 2*add;
    }

    // Now answer X-th largest
    ll seen = 0;
    for (auto [len, cnt] : freq) {
        if (seen + cnt >= X) {
            cout << fixed << setprecision(10) << (double)len << "\n";
            return;
        }
        seen += cnt;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--) solve();
    return 0;
}

