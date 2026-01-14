#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXA = 500000;

int mu[MAXA + 1];
vector<int> divisors[MAXA + 1];

// Precompute Möbius function μ(n) using a linear sieve
void mobius_sieve() {
    vector<int> primes;
    vector<int> is_comp(MAXA + 1, 0);
    mu[1] = 1;
    for (int i = 2; i <= MAXA; i++) {
        if (!is_comp[i]) {
            primes.push_back(i);
            mu[i] = -1;
        }
        for (int p : primes) {
            if (1LL * i * p > MAXA) break;
            is_comp[i * p] = 1;
            if (i % p == 0) {
                mu[i * p] = 0;
                break;
            } else {
                mu[i * p] = -mu[i];
            }
        }
    }
}

// Precompute divisors for all numbers up to MAXA
void precompute_divisors() {
    for (int i = 1; i <= MAXA; i++)
        for (int j = i; j <= MAXA; j += i)
            divisors[j].push_back(i);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    mobius_sieve();
    precompute_divisors();

    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    vector<bool> inShelf(n + 1, false);
    vector<int> freq(MAXA + 1, 0);  // freq[d] = how many numbers in shelf divisible by d

    ll active = 0;                  // number of active beers
    ll coprimePairsWeighted = 0;    // sum μ(d) * C(freq[d], 2)

    while (q--) {
        int x;
        cin >> x;
        int val = a[x];

        ll delta = 0;

        if (!inShelf[x]) {
            // ADD this beer
            for (int d : divisors[val]) {
                delta += 1LL * mu[d] * freq[d];
                freq[d]++;
            }
            coprimePairsWeighted += delta;
            active++;
            inShelf[x] = true;
        } else {
            // REMOVE this beer
            for (int d : divisors[val]) {
                freq[d]--;
                delta += 1LL * mu[d] * freq[d];
            }
            coprimePairsWeighted -= delta;
            active--;
            inShelf[x] = false;
        }

        ll totalPairs = active * (active - 1) / 2;
        ll score = totalPairs - coprimePairsWeighted;
        cout << score << '\n';
    }

    return 0;
}


