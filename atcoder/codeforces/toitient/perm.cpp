#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10000000;
vector<int> phi(MAXN + 1);
vector<int> best(MAXN + 1, -1);

bool isPermutation(int a, int b) {
    int cntA[10] = {0}, cntB[10] = {0};
    while (a) { cntA[a % 10]++; a /= 10; }
    while (b) { cntB[b % 10]++; b /= 10; }
    for (int i = 0; i < 10; ++i)
        if (cntA[i] != cntB[i]) return false;
    return true;
}

void computePhi() {
    for (int i = 1; i <= MAXN; ++i) phi[i] = i;
    for (int i = 2; i <= MAXN; ++i)
        if (phi[i] == i)
            for (int j = i; j <= MAXN; j += i)
                phi[j] -= phi[j] / i;
}

void precompute() {
    computePhi();
    int bestN = -1;
    long long bestNum = 1, bestDen = 0;

    for (int n = 2; n <= MAXN; ++n) {
        if (isPermutation(n, phi[n])) {
            long long num = n, den = phi[n];
            if (bestN == -1 || num * bestDen < bestNum * den ||
               (num * bestDen == bestNum * den && n > bestN)) {
                bestN = n;
                bestNum = num;
                bestDen = den;
            }
        }
        best[n] = bestN;
    }
}


    // int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    precompute();

    int T;
    cin >> T;
    while (T--) {
        int M;
        cin >> M;
        int ans = best[M - 1];
        if (ans == -1) cout << "No solution.\n";
        else cout << ans << "\n";
    }
    return 0;
}
