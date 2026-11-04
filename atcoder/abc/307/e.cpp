
#include <bits/stdc++.h>
using namespace std;

const long long MOD = 998244353;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, m;
    cin >> n >> m;

    long long same = 1, diff = 0;

    for (int i = 2; i <= n; i++) {
        long long nsame = diff;
        long long ndiff = ((m - 1) * same
                         + (m - 2) * diff) % MOD;

        same = nsame;
        diff = ndiff;
    }

    cout << m * diff % MOD << '\n';
    return 0;
}



// x x x x x x 


// weris wtw hewns wrw

//