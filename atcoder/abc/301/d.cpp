#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    long long n;
    cin >> s >> n;

    int m = s.size();
    long long ans = 0;

    // Set all mandatory 1 bits.
    for (int i = 0; i < m; i++) {
        if (s[i] == '1') {
            ans |= (1LL << (m - 1 - i));
        }
    }

    if (ans > n) {
        cout << -1 << '\n';
        return 0;
    }

    // Greedily set ? bits from most significant to least.
    for (int i = 0; i < m; i++) {
        if (s[i] == '?') {
            long long bit = 1LL << (m - 1 - i);

            if (ans + bit <= n) {
                ans += bit;
            }
        }
    }

    cout << ans << '\n';
}


// we ue