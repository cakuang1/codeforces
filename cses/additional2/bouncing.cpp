#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;
using ll = long long;

// gcd for C++11
ll mygcd(ll a, ll b) {
    while (b) {
        ll t = a % b;
        a = b;
        b = t;
    }
    return a;
}

// prety w
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        ll n, m;
        ull k;
        cin >> n >> m >> k;
        // 1D positions:
        ll pr = 2*(n - 1), pc = 2*(m - 1);
        ull kr = k % pr, kc = k % pc;
        ll r = 1 + ll(std::llabs( ll(kr) - (n - 1) ));
        ll c = 1 + ll(std::llabs( ll(kc) - (m - 1) ));

        // Count bounce events:
        ll v = k / ull(n - 1);
        ll h = k / ull(m - 1);
        ll g = mygcd(n-1, m-1);
        ll l = (n-1)/g * (m-1);  // lcm = (n-1)*(m-1)/g
        ll both = k / ull(l);
        ll bounces = v + h - both;
        
        // how would ou wesee tsi we eiz two w
        cout << r << " " << c << " " << bounces << "\n";
    }
    return 0;
}
