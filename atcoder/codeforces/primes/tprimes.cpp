#include <bits/stdc++.h>
using namespace std;
using ll = long long;

static const int MAXP = 1000000;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 1) Sieve primes up to MAXP
    vector<bool> is_composite(MAXP+1,false);
    set<ll> valid;  // will hold all p^2 for prime p

    for (int i = 2; i <= MAXP; i++) {
        if (!is_composite[i]) {
            // i is prime
            ll sq = 1LL * i * i;
            valid.insert(sq);
            // mark multiples
            if ((ll)i * i <= MAXP) {
                for (int j = i*i; j <= MAXP; j += i) {
                    is_composite[j] = true;
                }
            }
        }
    }

    // 2) Answer queries
    int n;
    cin >> n;
    while (n--) {
        ll x;
        cin >> x;
        // x is T-prime iff it's the square of a prime,
        // i.e. iff x is in our 'valid' set.
        cout << ( valid.count(x) ? "YES\n" : "NO\n" );
    }

    return 0;

}


