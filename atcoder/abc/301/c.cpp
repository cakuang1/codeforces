#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s, t;
    cin >> s >> t;

    vector<int> a(26, 0), b(26, 0);
    int x = 0, y = 0;

    for (char c : s) {
        if (c == '@') x++;
        else a[c - 'a']++;
    }

    for (char c : t) {
        if (c == '@') y++;
        else b[c - 'a']++;
    }

    string allowed = "atcoder";

    for (int i = 0; i < 26; i++) {
        char c = 'a' + i;

        if (allowed.find(c) == string::npos) {
            if (a[i] != b[i]) {
                cout << "No\n";
                return 0;
            }
        } else {
            if (a[i] > b[i])
                y -= a[i] - b[i];
            else
                x -= b[i] - a[i];
        }
    }

    cout << (x >= 0 && y >= 0 ? "Yes\n" : "No\n");
    return 0;
} 

// gww irsl wrs wer