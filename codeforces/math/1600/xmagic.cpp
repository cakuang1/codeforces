#include <bits/stdc++.h>

using namespace std;

bool get(long long a, long long b, long long x) {
    if (a == x || b == x) return true;
    if (a < b) swap(a, b);
    if (b > a - b) b = a - b;
    if (x > max(a, b) || a == 0 || b == 0) return false;
    long long cnt = max(1ll, (a - max(x, b)) / (2 * b));
    return get(a - b * cnt, b, x);
}


int main() {
#ifdef _DEBUG
    freopen("input.txt", "r", stdin);
//  freopen("output.txt", "w", stdout);
#endif
    
    int t;
    cin >> t;
    while (t--) {
        long long a, b, x;
        cin >> a >> b >> x;
        if (get(a, b, x)) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
        
    return 0;
}