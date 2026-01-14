#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll n, k;
    ll s;
    cin >> n >> k >> s;
    int maxStep = n - 1; // Max step in one move
    if (s < k || s > k * maxStep) {
        cout << "NO" << endl;
        return 0;
    }
    cout << "YES" << endl;
    int q = s / k; // Base distance per move
    int r = s % k; // Extra distance to be distributed
    int curr = 1; // Start at house 1

    for (int i = 0; i < k; i++) {
        int step = q + (r > 0 ? 1 : 0); // Use extra step if available
        r--; // Reduce extra steps if used
        
        // Move to the other side or back
        if (curr + step <= n) {
            curr += step;
        } else {
            curr -= step;
        } 

        cout << curr << " ";
    }
    cout << endl;
    
    return 0;
}
