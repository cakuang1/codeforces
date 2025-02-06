#include <bits/stdc++.h>
#include <atcoder/string>

using namespace std;
using namespace atcoder;

// Does s contain t as a substring?
bool contains(const string &s, const string &t) {
    int n = s.size(), m = t.size();
    vector<int> za = z_algorithm(t + s);
    for (int i = m; i <= n; i++) {
        if (za[i] >= m) return true;
    }
    return false;
}

int main() {
    int n;
    cin >> n;
    vector<string> s(n);
    for (int i = 0; i < n; i++) cin >> s[i];
    for (auto it = s.begin(); it < s.end();) {
        bool flag = false;
        for (auto jt = s.begin(); jt < s.end(); jt++) {
            if (jt != it) flag |= contains(*jt, *it);
        }
        if (flag) it = s.erase(it);
        else ++it;
    }
    n = s.size();
    vector d(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        string now = s[i];
        for (int j = 0; j < n; j++) {
            if (j != i) now += s[j];
        }
        vector<int> za = z_algorithm(now);
        int cur = s[i].size();
        for (int j = 0; j < n; j++) {
            if (j == i) continue;
            d[j][i] = s[i].size();
            for (int k = 0; k < s[j].size(); k++) {
                if (za[cur + k] >= s[j].size() - k) {
                    d[j][i] = k + s[i].size() - s[j].size();
                    break;
                }
            }
            cur += s[j].size();
        }
    }
    vector dp(1 << n, vector<int>(n, 1 << 30));
    for (int i = 0; i < n; i++) dp[1 << i][i] = s[i].size();
    for (int bit = 1; bit < (1 << n) - 1; bit++) {
        for (int i = 0; i < n; i++) {
            if (~bit >> i & 1) continue;
            for (int j = 0; j < n; j++) {
                if (bit >> j & 1) continue;
                dp[bit | 1 << j][j] = min(dp[bit | 1 << j][j], dp[bit][i] + d[i][j]);
            }
        }
    }
    cout << *min_element(dp.back().begin(), dp.back().end()) << endl;
}
