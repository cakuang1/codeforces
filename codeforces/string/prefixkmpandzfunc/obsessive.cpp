
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
const int MOD = 1000000007;
 
// Prefix function (KMP)
vector<int> prefix_function(const string &s) {
    int n = (int)s.size();
    vector<int> pi(n, 0);
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) j++;
        pi[i] = j;
    }
    return pi;
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    string s, t;
    cin >> s >> t;
    int n = s.size(), m = t.size();
 
    // build combined string for KMP
    string comb = t + "#" + s;
    vector<int> pi = prefix_function(comb);
 
    // mark good indices
    vector<bool> good(n + 1, false);
    for (int i = m + 1; i <= n + m; i++) {
        if (pi[i] == m) {
            int pos = i - m; // 1-based index in s
            good[pos] = true;
        }
    }
 
    vector<ll> a(n + 1, 0), q1(n + 1, 0), q2(n + 1, 0);
 
    for (int i = 1; i <= n; i++) {
        if (!good[i]) {
            a[i] = a[i - 1];
        } else {
            // formula: (i - m + 1) + q2[i - m]
            ll term1 = i - m + 1;
            ll term2 = q2[i - m];
            a[i] = (term1 + term2) % MOD;
        }
        q1[i] = (q1[i - 1] + a[i]) % MOD;
        q2[i] = (q2[i - 1] + q1[i]) % MOD;
    }
 
    cout << q1[n] % MOD << "\n";
    return 0;

