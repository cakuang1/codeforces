#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000000;

// gpd[i] = greatest prime divisor of i
int gpd[MAXN + 1];

// Precompute greatest prime divisors using sieve
void build_sieve() {
    for (int i = 2; i <= MAXN; ++i) {
        if (!gpd[i]) { // i is prime
            for (int j = i; j <= MAXN; j += i)
                gpd[j] = i;
        }
    }
}

// Factorize a number into {prime -> exponent}
map<int, int> factorize(int x) {
    map<int, int> factors;
    while (x > 1) {
        int p = gpd[x];
        int cnt = 0;
        while (x % p == 0) {
            x /= p;
            cnt++;
        }
        factors[p] = cnt;
    }
    return factors;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    build_sieve();

    int n;
    long long k;
    cin >> n >> k;

    vector<int> c(n);
    for (int i = 0; i < n; ++i)
        cin >> c[i];

    // Factorize k
    auto kfac = factorize((int)k);

    // Store the maximum exponent of each prime among all c[i]
    unordered_map<int, int> maxExp;
    for (int x : c) {
        auto f = factorize(x);
        for (auto &pr : f)
            maxExp[pr.first] = max(maxExp[pr.first], pr.second);
    }

    bool ok = true;
    for (auto &pr : kfac) {
        int p = pr.first;
        int need = pr.second;
        if (maxExp[p] < need) {
            ok = false;
            break;
        }
    }

    cout << (ok ? "Yes\n" : "No\n");
    return 0;
}

// r weronyl ifs twhe differe modial weo wer
// 