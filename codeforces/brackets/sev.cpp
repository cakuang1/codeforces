#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    string s;
    cin >> n >> s;

    if (n % 2 == 1) {
        cout << ":(" << "\n";
        return 0;
    }

    // Must start with '(' and end with ')'
    if (s[0] == ')') { cout << ":(" << "\n"; return 0; }
    if (s[n-1] == '(') { cout << ":(" << "\n"; return 0; }
    s[0] = '(';
    s[n-1] = ')';

    int open = n/2, close = n/2;
    for (char c : s) {
        if (c == '(') open--;
        if (c == ')') close--;
    }
    if (open < 0 || close < 0) { cout << ":(" << "\n"; return 0; }

    // Fill '?'
    for (int i = 1; i < n-1; i++) {
        if (s[i] == '?') {
            if (open > 0) {
                s[i] = '(';
                open--;
            } else {
                s[i] = ')';
                close--;
            }
        }
    }

    // Validate prefix conditions
    int bal = 0;
    for (int i = 0; i < n; i++) {
        bal += (s[i] == '(' ? 1 : -1);
        if (bal <= 0 && i < n-1) { // must stay positive until last
            cout << ":(" << "\n";
            return 0;
        }
    }

    if (bal != 0) { cout << ":(" << "\n"; return 0; }
    cout << s << "\n";
    return 0;
}

