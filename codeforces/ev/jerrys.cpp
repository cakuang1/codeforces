#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n; 
    if (!(cin >> n)) return 0;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    sort(a.begin(), a.end());

    if (n < 2) {
        cout << fixed << setprecision(10) << 0.0 << "\n";
        return 0;
    }

    // Differences are between distinct values; ai are distinct; ai ≤ 5000
    int maxA = a.back();
    int minA = a.front();
    int Dmax = maxA - minA;                // ≤ 4999
    if (Dmax == 0) {                       // all equal (not possible per statement), but safe
        cout << fixed << setprecision(10) << 0.0 << "\n";
        return 0;
    }

    vector<long long> cnt(Dmax + 1, 0);    // cnt[d] for d≥1; cnt[0] unused

    // Count unordered pairs and their differences
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            int d = a[i] - a[j];           // > 0 since sorted and distinct
            ++cnt[d];
        }
    }

    long double totalPairs = 1.0L * n * (n - 1) / 2.0L; // C(n,2)

    // Convolution conv = cnt * cnt over indices [1..Dmax]
    // Range of sums is [2..2*Dmax]
    vector<long long> conv(2 * Dmax + 1, 0);
    for (int d1 = 1; d1 <= Dmax; ++d1) if (cnt[d1]) {
        for (int d2 = 1; d2 <= Dmax; ++d2) if (cnt[d2]) {
            conv[d1 + d2] += cnt[d1] * cnt[d2];
        }
    }

    // Suffix sums of cnt to get number of third-round diffs strictly greater than s
    vector<long long> suf(2 * Dmax + 2, 0); // sized to index up to 2*Dmax
    long long running = 0;
    for (int d = Dmax; d >= 1; --d) {
        running += cnt[d];
        suf[d] = running;
    }

    // Accumulate numerator: sum_s conv[s] * (# of d > s)
    // Note: for s > Dmax, suf[s] = 0 (already initialized)
    long double num = 0.0L;
    for (int s = 2; s <= 2 * Dmax; ++s) {
        // We need count of d > s; suf uses index in [1..Dmax]
        long long greater_cnt = (s + 1 <= Dmax) ? suf[s + 1] : 0;
        if (greater_cnt == 0 || conv[s] == 0) continue;
        num += (long double)conv[s] * (long double)greater_cnt;
    }

    long double den = totalPairs * totalPairs * totalPairs;
    long double ans = (den == 0.0L) ? 0.0L : (num / den);

    cout.setf(std::ios::fixed);
    cout << setprecision(10) << (double)ans << "\n";
    return 0;
}

