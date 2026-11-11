
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll MOD = 998244353;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    string s;
    cin >> n >> s;

    // Adjacent digits greater than 1 cause an infinite loop
    for (int i = 0; i + 1 < n; i++) {
        if (s[i] != '1' && s[i + 1] != '1') {
            cout << -1 << '\n';
            return 0;
        }
    }

    ll ans = 0;

    // Process digits from right to left
    for (int i = n - 1; i >= 1; i--) {
        int x = s[i] - '0';
        ans = (ans + 1) * x % MOD;
    }

    cout << ans << '\n';

    return 0;
}
 


// wevwirtwlthse prars sls fowr
/// wer-o es= smusns erns ainower
// wc nwetwd werdi wer

// ewvneutsl ltsod this esrsmsutw hd wnerw