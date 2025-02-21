#include <bits/stdc++.h>
using namespace std;
 
typedef unsigned long long ull;
 
// Our limit for n
const ull LIMIT = 1000000000000000000ULL; // 1e18
 
// Precompute binomial coefficients up to MAXB (70 is safe).
const int MAXB = 70;
ull binom[MAXB][MAXB];
 
void initBinom() {
    for (int i = 0; i < MAXB; i++){
        binom[i][0] = 1;
        binom[i][i] = 1;
        for (int j = 1; j < i; j++){
            binom[i][j] = binom[i-1][j-1] + binom[i-1][j];
        }
    }
}
 
// countUpTo(X, k) returns the number of numbers in [0, X] that have exactly k ones.
// We use the standard digit-DP idea but in a combinatorial way.
ull countUpTo(ull X, int k) {
    if (X == 0)
        return (k == 0 ? 1ULL : 0ULL);
    int bits = 64 - __builtin_clzll(X); // number of bits needed to represent X
    ull ans = 0;
    // Process bits from most significant (bit index bits-1) to least significant (index 0)
    for (int i = bits - 1; i >= 0; i--) {
        if (X & (1ULL << i)) {
            // If this bit is 1, then for numbers that have 0 at this position (and are less than X),
            // we can freely choose the remaining i bits to have exactly k ones.
            if (i >= k)
                ans += binom[i][k];
            // Since X has a 1 here, we "use" one 1 and move on.
            k--;
            if (k < 0)
                break;
        }
    }
    // If we used exactly k ones, then X itself has exactly the required ones.
    if (k == 0) ans++;
    return ans;
}
 
// Count numbers in [L, R] with exactly k ones.
ull countRange(ull L, ull R, int k) {
    if (L == 0)
        return countUpTo(R, k);
    else
        return countUpTo(R, k) - countUpTo(L - 1, k);
}
 
// For a given n, we want the count of numbers in [n+1, 2n] that have exactly k ones.
ull countInterval(ull n, int k) {
    return countRange(n + 1, 2 * n, k);
}
 
// Main: Given m and k (m: target count, k: number of ones), find any n (1 <= n <= 1e18) such that 
// countInterval(n, k) equals m. (Problem guarantees an answer exists.)
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    initBinom();
    ull m;
    int k;
    cin >> m >> k;
 
    // We'll binary search on n in [1, LIMIT].
    ull lo = 1, hi = LIMIT;
    ull ans = 0;
    bool found = false;
    while (lo <= hi) {
        ull mid = lo + (hi - lo) / 2;
        ull cnt = countInterval(mid, k);
        if (cnt == m) {
            ans = mid;
            found = true;
            break; // any valid answer is acceptable
        } else if (cnt < m) {
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    if (!found)
        cout << -1 << "\n"; // Should not happen per problem statement.
    else
        cout << ans << "\n";
    return 0;
}
