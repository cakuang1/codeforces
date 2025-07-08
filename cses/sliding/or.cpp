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

    // Circular buffer to remember the last k values
    vector<uint32_t> buf(k);
    // Count of set bits in the current window
    int cnt[32] = {0};

    // Fill first window
    buf[0] = uint32_t(x);
    for(int bit=0;bit<32;bit++)
        cnt[bit] = ((buf[0] >> bit) & 1);
    ll window_or = buf[0];
    for(int i=1; i<k; i++){
        x = (a*x + b) % c;
        buf[i] = uint32_t(x);
        window_or |= buf[i];
        for(int bit=0;bit<32;bit++){
            cnt[bit] += ((buf[i]>>bit)&1);
        }
    }

    // XOR of all window‐ORs
    ll answer = window_or;

    int pos = 0;  // where to overwrite next in the circular buffer

    // Slide the window
    for(ll i = k; i < n; i++){
        // generate next value
        x = (a*x + b) % c;
        uint32_t in = uint32_t(x);
        uint32_t out = buf[pos];
        buf[pos] = in;

        // union of bits we must update
        uint32_t U = out | in;
        while(U){
            int bit = __builtin_ctz(U);
            U &= U-1;
            // remove outgoing bit
            if((out >> bit) & 1){
                if(--cnt[bit] == 0){
                    // if count drops to zero, unset in window_or
                    window_or &= ~(1u<<bit);
                }
            }
            // add incoming bit
            if((in >> bit) & 1){
                if(cnt[bit]++ == 0){
                    // if count was zero, set in window_or
                    window_or |= (1u<<bit);
                }
            }
        }
                
        answer ^= window_or;
        if(++pos == k) pos = 0;
    }
    // go bitwisew ew
    cout << answer << "\n";
    return 0;
}
