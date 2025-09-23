#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;

    int needOpen = k / 2;
    int needClose = k / 2;
    string res;

    for (char c : s) {
        if (c == '(' && needOpen > 0) {
            res.push_back(c);
            needOpen--;
        } else if (c == ')' && needClose > 0 && (int)res.size() < k) {
            res.push_back(c);
            needClose--;
        }
        if ((int)res.size() == k) break;
    }

    cout << res << "\n";
    return 0;
}
