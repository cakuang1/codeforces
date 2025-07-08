#include <iostream>
#include <vector>
#include <set>

using namespace std;

const unsigned int MAX_A = 1'000'000;
vector<unsigned int> sieve(MAX_A + 1);
vector<unsigned int> prime;

unsigned int gcd(unsigned int a, unsigned int b) {
    return b == 0 ? a : gcd(b, a % b);
}

unsigned int solve() {

    unsigned int n;
    cin >> n;
    vector<unsigned int> a(n);
    for (unsigned int i = 0; i < n; i++) {
        cin >> a[i];
    }

    unsigned int common = a[0];
    vector<set<unsigned int>> facts(n);
    for (unsigned int i = 1; i < n; i++) {
        common = gcd(common, a[i]);
    }
    for (unsigned int i = 0; i < n; i++) {
        unsigned int t = a[i] / common;
        while (t != 1) {
            facts[i].insert(sieve[t]);
            t /= sieve[t];
        }
    }

    unsigned int answer = 0;
    for (unsigned int i = 0; i < n; i++) {
        for (unsigned int p : facts[i]) {
            int l = (i + n - 1) % n, r = i;
            unsigned int cnt = 0;
            while (facts[l].count(p) > 0) {
                facts[l].erase(p);
                l--; cnt++;
                if (l < 0) {
                    l = n - 1;
                }
            }
            while (facts[r].count(p) > 0) {
                if (r != i) {
                    facts[r].erase(p);
                }
                ++r %= n; cnt++;
            }
            answer = max(answer, cnt);
        }
        facts[i].clear();
    }

    return answer;

} 

// greedily w
int main() {

    sieve[1] = 1;
    for (unsigned int i = 2; i <= MAX_A; i++) {
        if (sieve[i] == 0) {
            sieve[i] = i;
            prime.push_back(i);
        }
        for (unsigned int j = 0; j < prime.size() && prime[j] <= sieve[i] && i * prime[j] <= MAX_A; j++) {
            sieve[i * prime[j]] = prime[j];
        }
    }
    
    // determine the min and min count? 
    
    // if the gcd wew 
    unsigned int t;
    cin >> t;
    for (unsigned int i = 0; i < t; i++) {
        cout << solve() << '\n';
    }

}