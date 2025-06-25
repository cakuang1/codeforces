#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve() {
    int n, c;
    cin >> n >> c;

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    if (n == 1) {
        cout << "0\n";
        return;
    }

    int mx = *max_element(a.begin() + 1, a.end());
    int mxc = max(a[0] + c, mx);
    int winner = mxc == a[0] + c ? 0 : find(a.begin() + 1, a.end(), mx) - a.begin();
    ll sum = c;
    for (int i = 0; i < n; sum += a[i], ++i) {
        int answer;
        if (i == winner) {
            answer = 0;
        } else if (sum + a[i] >= mx) {
            answer = i;
        } else {
            answer = i + 1;
        }
        cout << answer << " \n"[i == n - 1];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int test = 1;
    cin >> test;
    
    while (test--) {
       solve();
    }

    return 0;
}