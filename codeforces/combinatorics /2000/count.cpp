#include <iostream>
#include <cstdio>
#define maxn 1000100
#define ll long long
using namespace std;

const int p = 1000000007;

ll pow_mod(ll x, ll n) {
    ll s = 1;
    for (; n; n >>= 1) {
        if (n & 1) s = s * x % p;
        x = x * x % p;
    }
    return s;
} 


// 
ll fac[maxn], inv[maxn];
void init_C(int n) {
    fac[0] = 1; for (int i = 1; i <= n; ++i) fac[i] = fac[i - 1] * i % p;
    inv[n] = pow_mod(fac[n], p - 2); for (int i = n - 1; ~i; --i) inv[i] = inv[i + 1] * (i + 1) % p;
}

ll C(int n, int m) { return n < m ? 0 : fac[n] * inv[m] % p * inv[n - m] % p; }

int n, m; 

void work() {
    cin >> m >> n; ll ans = 1; 
    for (int i = 2; i * i <= m; ++i) 
        if (m % i == 0) {
            int s = 0;
            while (m % i == 0) m /= i, ++s;
            ans = ans * C(s + n - 1, n - 1) % p; 
        }
    if (m > 1) ans = ans * n % p; 
    cout << ans * pow_mod(2, n - 1) % p << "\n";
} 

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int T; cin >> T; init_C(1000020);
    while (T--) work(); 
    return 0;
} 