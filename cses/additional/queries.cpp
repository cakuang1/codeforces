#include <bits/stdc++.h>
using namespace std;

// gcd for C++11
long long mygcd(long long x, long long y) {
    while (y) {
        long long t = x % y;
        x = y;
        y = t;
    }
    return x;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    while(n--){
        long long a, b, x;
        cin >> a >> b >> x;
        // Must fit in A, and x must be a multiple of gcd(a,b).
        long long g = mygcd(a,b);
        if (x <= a && x % g == 0) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }

    return 0;
}

