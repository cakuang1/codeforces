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

    // generate first k elements and xor them
    vector<uint32_t> buf(k);
    uint32_t cur = x;
    buf[0] = cur;
    for(int i = 1; i < k; i++){
        cur = (a*cur + b) % c;
        buf[i] = cur;
    }
    uint32_t window_xor = 0;
    for(int i = 0; i < k; i++)
        window_xor ^= buf[i];

    uint32_t answer = window_xor;
    int pos = 0;

    // slide
    for(ll i = k; i < n; i++){
        // generate x_i
        x = (a*x + b) % c;
        uint32_t in = x;
        uint32_t out = buf[pos];
        buf[pos] = in;

        // update xor
        window_xor ^= out;   // remove
        window_xor ^= in;    // add

        answer ^= window_xor;

        if(++pos == k) pos = 0;
    }

    cout << answer << "\n";
    return 0;
}
