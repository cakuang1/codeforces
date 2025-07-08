#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, k;
    cin >> n >> k;
    ll x, a, b, c;
    cin >> x >> a >> b >> c;

    // We'll keep the last k values in a circular buffer
    vector<ll> buf(k);
    // generate x1
    buf[0] = x;
    ll sum = x;

    // generate x2..xk to fill our first window
    for(int i = 1; i < k; i++){
        x = (a * x + b) % c;
        buf[i] = x;
        sum += x;
    }

    // res = xor of all window sums
    ll res = sum;

    // now slide the window over the remaining n-k values
    // buf[pos] will overwrite the oldest element
    int pos = 0;
    for(ll i = k; i < n; i++){
        // generate next x_{i+1}
        x = (a * x + b) % c;

        // subtract the element we're ejecting
        sum -= buf[pos];
        // add the new one
        sum += x;
        // overwrite in buffer
        buf[pos] = x;

        // advance the circular index
        if (++pos == k) pos = 0;

        // xor into result
        res ^= sum;
    }

    cout << res << "\n";
    return 0;
}
 

// how would you  only w