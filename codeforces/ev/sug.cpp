#include <bits/stdc++.h>
using namespace std;

// Compute expected number of moves to reach N from 0 on a dice (1..M)
// with "bad" squares that teleport to 0. If impossible, print -1.
// Input format:
//   N M K
//   a_1 a_2 ... a_K   (1-based indices of bad squares; 1..N-1 only)
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, K;
    if (!(cin >> N >> M >> K)) return 0;
    vector<int> bad(N+1, 0); // bad[i]=1 if square i teleports to 0
    for (int i = 0; i < K; ++i) {
        int x; cin >> x;
        if (1 <= x && x <= N-1) bad[x] = 1;
    }

    // Check impossibility: M consecutive bad squares anywhere in [1..N-1]
    int run = 0, maxRun = 0;
    for (int i = 1; i <= N-1; ++i) {
        if (bad[i]) { run++; maxRun = max(maxRun, run); }
        else run = 0;
    }
    if (maxRun >= M) {
        cout << -1 << "\n";
        return 0;
    }

    // Affine form g(i) = a[i] * X + b[i], with X = f(0).
    // For i >= N, a[i]=b[i]=0 (already at/after goal).
    vector<long double> a(N + M + 5, 0.0L), b(N + M + 5, 0.0L);

    // Sliding window sums over the next M positions:
    long double sumA = 0.0L, sumB = 0.0L; // = sum_{k=1..M} a[i+k], b[i+k]
    // Initially for i = N-1, the window is i+1..i+M = N..N+M-1; all zero.

    for (int i = N - 1; i >= 0; --i) {
        if (bad[i]) {
            a[i] = 1.0L;
            b[i] = 0.0L;
        } else {
            a[i] = sumA / (long double)M;
            b[i] = sumB / (long double)M + 1.0L;
        }
        // Slide window backward: next i' = i-1 will need sum over [i..i+M-1]
        sumA += a[i] - a[i + M];
        sumB += b[i] - b[i + M];
    }

    long double A0 = a[0], B0 = b[0];
    // X = A0*X + B0  =>  (1 - A0) * X = B0
    long double denom = 1.0L - A0;
    // By the earlier impossibility check, denom > 0 here.
    long double ans = B0 / denom;

    cout.setf(std::ios::fixed); cout << setprecision(15) << (double)ans << "\n";
    return 0;
}

