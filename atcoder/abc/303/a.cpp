#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    string s, t;
    cin >> n >> s >> t;

    for (int i = 0; i < n; i++) {
        if (s[i] == t[i]) continue;

        if ((s[i] == '1' && t[i] == 'l') ||
            (s[i] == 'l' && t[i] == '1') ||
            (s[i] == '0' && t[i] == 'o') ||
            (s[i] == 'o' && t[i] == '0')) {
            continue;
        }

        cout << "No\n";
        return 0;
    }

    cout << "Yes\n";
    return 0;
}