#include <iostream>
#include <cmath>
using namespace std;

using ll = long long;

// Function to calculate the number of digits in a number
int countDigits(ll n) {
    int digits = 0;
    while (n) {
        digits++;
        n /= 10;
    }
    return digits;
}

// Function to calculate F(A, B)
int f(ll a, ll b) {
    return max(countDigits(a), countDigits(b));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    ll n;
    cin >> n;

    int ans = 1e9; // Initialize to a large value
    for (ll i = 1; i * i <= n; i++) {
        if (n % i == 0) { // Check if i is a divisor of n
            ll other = n / i;
            ans = min(ans, f(i, other));
        }
    }
    cout << ans << endl;
    return 0;
}
