#include <iostream>
#include <vector>
#include <cmath>
#include <set>

using namespace std;

// Function to perform the Sieve of Eratosthenes to find all primes up to a given limit
vector<long long> sieve(long long limit) {
    vector<bool> is_prime(limit + 1, true);
    vector<long long> primes;
    is_prime[0] = is_prime[1] = false;
    for (long long i = 2; i <= limit; ++i) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (long long j = i * i; j <= limit; j += i) {
                is_prime[j] = false;
            }
        }
    }
    return primes;
}

int main() {
    // Generate all prime numbers up to 10^6
    vector<long long> primes = sieve(1000000);
    set<long long> t_primes;

    // Generate T-primes (squares of primes)
    for (long long prime : primes) {
        long long t_prime = prime * prime;
        if (t_prime <= 1000000000000LL) {
            t_primes.insert(t_prime);
        }
    }

    // Read input
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        long long x;
        cin >> x;
        if (t_primes.count(x)) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }

    return 0;
}
