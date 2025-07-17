#include <bits/stdc++.h>
 
using namespace std;
 
#define int long long
 
int f(int s, int k) {
    // (s + 20x) * (k - 4x)
    // (-80)x^2 + (20k - 4s)x + (sk)
    // -b/2a = (5k-s)/40
    int x = (5 * k - s) / 40;
    x = min(x, k / 4);
    int res = s * k;
    if (x > 0) {
        res = max(res, (s + 20 * x) * (k - 4 * x));
    }
    x = min(x + 1, k / 4);
    if (x > 0) {
        res = max(res, (s + 20 * x) * (k - 4 * x));
    }
    return res;
}
 
int32_t main() {
    int t;
    cin >> t;
    while (t--) {
        int s, k;
        cin >> s >> k;
        int ans = s * k;
        if (s % 10 == 5) {
            ans = max(ans, (s + 5) * (k - 1));
        } else if (s % 10) {
            if (s % 2 == 1) {
                s += s % 10;
                --k;
            }
            for (int i = 0; i < 4; ++i) {
                if (k > 0) {
                    ans = max(ans, f(s, k));
                }
                s += s % 10;
                --k;
            }
        }
        cout << ans << "\n";
    }
    return 0;
} 

