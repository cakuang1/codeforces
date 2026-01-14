#include <iostream>
#include <vector>
using namespace std;

const int MOD = 1000000007;
vector<int> fac;
vector<int> ifac;

int binExp(int base, int exp) {
    base %= MOD;
    int res = 1;
    while (exp > 0) {
        if (exp & 1) {
            res = (int) ((long long) res * base % MOD);
        }
        base = (int) ((long long) base * base % MOD);
        exp >>= 1;
    }
    return res;
}

void precompute(int n) {
    fac.resize(n + 1);
    fac[0] = fac[1] = 1;
    for (int i = 2; i <= n; i++) {
        fac[i] = (int) ((long long) i * fac[i-1] % MOD);
    }

    ifac.resize(n + 1);
    for (int i = 0; i < fac.size(); i++) {
        ifac[i] = binExp(fac[i], MOD - 2);
    }
    return;
}

int nCr(int n, int r) {
    if ((n < 0) || (r < 0) || (r > n)) {
        return 0;
    }
    return (int) ((long long) fac[n] * ifac[r] % MOD * ifac[n - r] % MOD);
}

int countValidBitonicPerm(int n, int i, int j, int x, int y) {
    if (x > y) {
        i = n - i + 1;
        j = n - j + 1;
        swap(i, j);
        swap(x, y);
    }

    int sum = 0;
    for (int k = i + 1; k < j; k++) {
        sum += nCr(n - y - 1, j - k - 1);
        sum %= MOD;
    }
    int count = (int) ((long long) nCr (x - 1, i - 1) * nCr(y - x - 1, n - j - (x - i)) % MOD * sum % MOD);

    sum = 0;
    for (int k = j + 1; k < n; k++) {
        sum += nCr(n - y - 1, k - j - 1);
        sum %= MOD;
    }
    count += (int) ((long long) nCr(x - 1, i - 1) * nCr(y - x - 1, j - i - 1) % MOD * sum % MOD);
    count %= MOD;

    if (y == n) {
        if (j == n) {
            return 0;
        } else {
            return (int) ((long long) nCr(x - 1, i - 1) * nCr(y - x - 1, j - i - 1) % MOD);
        }
    }
    
    return count;
}

int main() {
    const int MAXN = 100;
    precompute(MAXN);

    int testCases;
    cin >> testCases;
    for (int test = 1; test <= testCases; test++) {
        int n, i, j, x, y;
        cin >> n >> i >> j >> x >> y;
        cout << countValidBitonicPerm(n, i, j, x, y) << endl;
    }

    return 0;
}