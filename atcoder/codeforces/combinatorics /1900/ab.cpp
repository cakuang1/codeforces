#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    string s;
    cin >> n >> s;

    long long res = 1LL * n * (n - 1) / 2; // Compute n * (n-1) / 2

    for (int x = 0; x < 2; x++) {
        int cur = 1;
        for (int i = 1; i < n; i++) {
            if (s[i] == s[i - 1]) {
                cur++;
            } else {
                res -= cur - x;
                cur = 1;
            }
        }
        reverse(s.begin(), s.end()); // Reverse the string for the second pass
    }

    cout << res << endl;
    return 0;
}
