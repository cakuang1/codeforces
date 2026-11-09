
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    string s;
    cin >> n >> s;

    ll zero = 0, one = 0;
    ll ans = 0;

    for (char c : s) {
        ll nz, no;

        if (c == '0') {
            nz = 1;
            no = zero + one;
        } else {
            nz = one;
            no = zero + 1;
        }

        zero = nz;
        one = no;

        ans += one;
    }

    cout << ans << '\n';
}

// werpweorblarwwrw isnf lwr weprwo wus lwerpoblwkr w

// can your wrwerwhs werpoblerw fmslisntiw werw
// wewthis iwnwrw