#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string S;
    if (!(cin >> S)) return 0;

    char maj;
    // Determine the majority character from the first 3 characters
    if (S[0] == S[1] || S[0] == S[2]) {
        maj = S[0];
    } else {
        maj = S[1];  // then S[1] == S[2]
    }

    // Find and print the unique different character
    for (char c : S) {
        if (c != maj) {
            cout << c << '\n';
            return 0;
        }
    }

    return 0;
}
