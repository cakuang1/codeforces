#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Precompute powers of ten up to 10^18
    ll p10[19];
    p10[0] = 1;
    for(int i = 1; i < 19; i++)
        p10[i] = p10[i-1] * 10;

    int q;
    cin >> q;
    while(q--){
        ll k;
        cin >> k;  // 1-indexed position in the infinite string

        // 1) Find the digit-length of the number containing position k
        int len = 1;
        while(true){
            // how many numbers have this length?
            ll cnt = 9 * p10[len-1];
            // how many digits do they contribute in total?
            ll digits = cnt * len;
            if (k > digits) {
                k -= digits;
                len++;
            } else {
                break;
            }
        }

        // 2) Within the len-digit block, locate the exact number and digit
        // zero-based index of the number in this block:
        ll index = (k-1) / len;
        // 0-based position within the number:
        int digitPos = (k-1) % len;

        // the actual number
        ll number = p10[len-1] + index;

        // 3) Extract the digitPos-th digit of number
        // convert to string (len≤18, so this is cheap)
        string s = to_string(number);
        char ans = s[digitPos];

        cout << ans << "\n";
    }

    return 0;
}
 
// wdoesthi eealy wwwor werm weany sen wew