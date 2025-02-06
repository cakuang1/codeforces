#include <iostream>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    ll N;
    cin >> N;

    // If N is odd, f(N) ends in 0 (no trailing zeros)
    if (N % 2 != 0) {
        cout << 0 << endl;
        return 0;
    }

    // Count the number of factors of 5 in all even numbers up to N


    ll count_5 = 0;
    for (ll i = 10; i <= N; i *= 5) {
        count_5 += N / i;
    }
    
    // count all factors  w

    cout << count_5 << endl;
    return 0;
}
