#include <bits/stdc++.h>
using namespace std;

vector<int> sieve(int limit) {
    vector<bool> is_prime(limit + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= limit; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= limit; j += i) {
                is_prime[j] = false;
            }
        }
    }
    vector<int> primes;
    for (int i = 2; i <= limit; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
        }
    }
    return primes;
}

int countNumbersWith9Divisors(long long N) {
    // Primes needed for Case 1 (p^8) and Case 2 (p1^2 * p2^2)
    long long limit_case1 = pow(N, 1.0 / 8);
    long long limit_case2 = sqrt(N);

    vector<int> primes_case1 = sieve(limit_case1);
    vector<int> primes_case2 = sieve(limit_case2);

    int count = 0;

    // Case 1: p^8
    for (int p : primes_case1) { 
        long long power = 1;
        for (int i = 0; i < 8; i++) {
            power *= p;
            if (power > N) break;
        }
        if (power <= N) count++;
    }

    // Case 2: p1^2 * p2^2
    for (int i = 0; i < primes_case2.size(); i++) {
        long long p1_square = 1LL * primes_case2[i] * primes_case2[i];
        if (p1_square > N) break; // Early termination for larger primes
        for (int j = i + 1; j < primes_case2.size(); j++) {
            long long p2_square = 1LL * primes_case2[j] * primes_case2[j];
            if (p1_square > N / p2_square) break; // Avoid overflow
            long long product = p1_square * p2_square;
            if (product <= N) count++;
        }
    }

    return count;
}

int main() {
    long long N;
    cin >> N;
    int result = countNumbersWith9Divisors(N);
    cout << result << endl;
    return 0;
}
