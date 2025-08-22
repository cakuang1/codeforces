#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll MOD = 1000000007;

// 2×2 matrix for recurrence g(n) = g(n-1) + e * g(n-2)
struct Mat {
    ll a, b, c, d;
    // represents [ [a, b],
    //            [c, d] ]
};

// multiply two 2×2 matrices modulo MOD
Mat mul(const Mat &x, const Mat &y) {
    return {
        (x.a*y.a + x.b*y.c) % MOD,
        (x.a*y.b + x.b*y.d) % MOD,
        (x.c*y.a + x.d*y.c) % MOD,
        (x.c*y.b + x.d*y.d) % MOD
    };
}

// fast exponentiation of a 2×2 matrix
Mat mpow(Mat base, ll exp) {
    Mat res = {1, 0, 0, 1};  // identity
    while (exp > 0) {
        if (exp & 1) res = mul(res, base);
        base = mul(base, base);
        exp >>= 1;
    }
    return res;
}

// Compute g(n) for the recurrence:
//   g(0)=1, g(1)=1+e, and for n>=2: g(n)=g(n-1) + e*g(n-2)
// in O(log n) matrix exponentiation.
ll get_g(ll n, ll e) {
    if (n == 0) return 1;
    if (n == 1) return (1 + e) % MOD;
    // Recurrence matrix M = [ [1, e],
    //                         [1, 0] ]
    Mat M = {1, e % MOD, 1, 0};
    // We want M^(n-1) * [g(1), g(0)]^T, then take the first component.
    Mat P = mpow(M, n - 1);
    ll g1 = (1 + e) % MOD;
    ll g0 = 1;
    ll gn = (P.a * g1 + P.b * g0) % MOD;
    return gn;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Precompute primes up to sqrt(1e9) ≈ 31623
    const int LIMIT = 31623;
    vector<int> primes;
    vector<bool> is_composite(LIMIT+1, false);
    for (int i = 2; i <= LIMIT; i++) {
        if (!is_composite[i]) {
            primes.push_back(i);
            if ((ll)i * i <= LIMIT) {
                for (int j = i*i; j <= LIMIT; j += i)
                    is_composite[j] = true;
            }
        }
    }

    int t;
    cin >> t;
    while (t--) {
        ll n, k;
        cin >> n >> k;
        ll answer = 1;

        // Factor k by trial division
        for (int p : primes) {
            if ((ll)p * p > k) break;
            if (k % p == 0) {
                ll e = 0;
                while (k % p == 0) {
                    k /= p;
                    e++;
                }
                // multiply by the count for this prime's exponent
                answer = (answer * get_g(n, e)) % MOD;
            }
        }
        // If k>1 now, it's a prime factor > LIMIT with exponent 1
        if (k > 1) {
            answer = (answer * get_g(n, 1)) % MOD;
        }

        cout << answer << "\n";
    }

    
    // 
    
    return 0;
}
