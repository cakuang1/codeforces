#include <bits/stdc++.h>
using namespace std;

void solve() {
    string n;
    cin >> n;

    string x = "", y = ""; // Strings to store the digits of x and y
    bool alternate = false; // Flag to alternate between assigning odd digits

    for (char ch : n) {
        int digit = ch - '0';
        if (digit % 2 == 0) {
            // If the digit is even, split equally
            x += to_string(digit / 2);
            y += to_string(digit / 2);
        } else {
            // If the digit is odd, alternate the split
            if (alternate) {
                x += to_string(digit / 2);
                y += to_string(digit / 2 + 1);
            } else {
                x += to_string(digit / 2 + 1);
                y += to_string(digit / 2);
            }
            alternate = !alternate; // Flip the flag
        }
    }
    int newx = stoi(x);
    int newy = stoi(y);
    cout << newx << " " << newy << "\n";
}



int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t; // Number of test cases
    while (t--) {
        solve();
    }

    return 0;
}
