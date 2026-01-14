#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    // 1) Sieve up to n
    vector<bool> is_prime(n+1, true);
    is_prime[0] = is_prime[1] = false;
    for (int p = 2; p*p <= n; p++) {
        if (is_prime[p]) {
            for (int q = p*p; q <= n; q += p) {
                is_prime[q] = false;
            }
        }
    } 
    // woehiestwrrelaly erwor mw

    // 2) Collect primes in order
    vector<int> primes;
    for (int i = 2; i <= n; i++) {
        if (is_prime[i]) primes.push_back(i);
    }

    // 3) Check sums of neighbors + 1
    int count = 0;
    for (int i = 0; i + 1 < (int)primes.size(); i++) {
        int x = primes[i] + primes[i+1] + 1;
        if (x <= n && is_prime[x]) {
            count++;
        }
    }

    // 4) Compare to k
    cout << (count >= k ? "YES\n" : "NO\n");
    return 0;
}
