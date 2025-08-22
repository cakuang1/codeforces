#include <bits/stdc++.h>
using namespace std;
static const int MAXX = 5000;
static const int MOD  = 1000000007;

// fast modular exponentiation
long long modexp(long long a, long long e) {
    long long res = 1;
    a %= MOD;
    while (e > 0) {
        if (e & 1) res = (res * a) % MOD;
        a = (a * a) % MOD;
        e >>= 1;
    }
    return res;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> x(n);
    for(int i = 0; i < n; i++){
        cin >> x[i];
    }

    // 1) sieve primes up to MAXX
    vector<int> primes;
    vector<bool> is_comp(MAXX+1,false);
    for(int i = 2; i <= MAXX; i++){
        if (!is_comp[i]) {
            primes.push_back(i);
            if ((long long)i * i <= MAXX)
                for(int j = i*i; j <= MAXX; j += i)
                    is_comp[j] = true;
        }
    }
    int P = primes.size();             // ~669

    // 2) build bit‐matrix: each row is a bitset of length P
    const int BITS = 700;  // >= P
    vector< bitset<BITS> > a(n);
    for(int i = 0; i < n; i++){
        int v = x[i];
        for(int j = 0; j < P && primes[j]*primes[j] <= v; j++){
            int p = primes[j];
            int cnt = 0;
            while (v % p == 0) {
                v /= p;
                cnt ^= 1;   // only parity matters
            }
            if (cnt) a[i].flip(j);
        }
        if (v > 1) {
            // v is now a prime > sqrt(MAXX)
            // find its index
            int idx = int(lower_bound(primes.begin(), primes.end(), v) - primes.begin());
            // it must be in the list
            a[i].flip(idx);
        }
    }
    int rank = 0;
    for(int col = 0; col < P && rank < n; col++){
        // find a pivot row with a 1 in this column
        int pivot = -1;
        for(int r = rank; r < n; r++){
            if (a[r].test(col)) { pivot = r; break; }
        }
        if (pivot < 0) continue;    // no pivot in this col

        // swap pivot row into position 'rank'
        swap(a[pivot], a[rank]);

        // eliminate below
        for(int r = rank+1; r < n; r++){
            if (a[r].test(col)) {
                a[r] ^= a[rank];
            }
        }
        rank++;
    }

    // 4) answer = 2^(n - rank) mod
    cout << modexp(2, n - rank) << "\n";
    return 0;
}
