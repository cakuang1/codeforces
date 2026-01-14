#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const int MAXA = 5000000;
    vector<int> spf(MAXA+1, 0), f(MAXA+1, 0);
    vector<int> primes;
    primes.reserve(348513); // approx #primes ≤ 5e6

    // 1) Linear sieve to compute smallest prime factor (spf)
    for (int i = 2; i <= MAXA; i++) {
        if (!spf[i]) {
            spf[i] = i;
            primes.push_back(i);
        }
        for (int p: primes) {
            ll x = ll(i) * p;
            if (x > MAXA || p > spf[i]) break;
            spf[x] = p;
        }
    }

    // 2) Compute f[i] = number of prime factors of i (with multiplicity)
    f[1] = 0;
    for (int i = 2; i <= MAXA; i++) {
        f[i] = f[i / spf[i]] + 1;
    }

    // 3) Build prefix sums: F[i] = sum_{j=2..i} f[j]
    vector<ll> F(MAXA+1, 0);
    for (int i = 2; i <= MAXA; i++) {
        F[i] = F[i-1] + f[i];
    }

    // 4) Answer queries
    int t;
    cin >> t;
    while (t--) {
        int a, b;
        cin >> a >> b;
        // score = total prime factors in a!/b!
        cout << (F[a] - F[b]) << "\n";
    }
    return 0;
}

