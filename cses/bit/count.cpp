#include <bits/stdc++.h>
using namespace std;
using i128 = __int128_t;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n;
    cin >> n;
    // We'll sum in 128-bit to avoid overflow
    i128 total = 0;
    i128 N = (i128)n + 1;

    for(int k = 0; (1LL<<k) <= n; k++){
        i128 block = i128(1) << (k+1);
        i128 full  = N / block;
        i128 rem   = N % block;
        i128 ones_in_full = full * (i128(1) << k);
        i128 ones_in_rem  = rem > (i128(1)<<k) ? rem - (i128(1)<<k) : 0;
        total += ones_in_full + ones_in_rem;
    }

    // Print total (fits in 64-bit since n<=1e15 => sum ~ n log n)
    long long ans = (long long)total;
    cout << ans << "\n";
    return 0;
}
