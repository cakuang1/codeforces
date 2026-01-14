#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string X;
    cin >> X;

    vector<int> cnt(10, 0);
    for (char c : X) cnt[c - '0']++;

    // Step 1: find smallest non-zero digit
    int first = -1;
    for (int d = 1; d <= 9; d++) {
        if (cnt[d] > 0) {
            first = d;
            cnt[d]--;
            break;
        }
    }

    // print first digit
    cout << first;

    // print remaining digits sorted
    for (int d = 0; d <= 9; d++) {
        while (cnt[d]--) cout << d;
    }

    return 0;
}
