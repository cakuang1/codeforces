#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// Function to find the GCD of two integers
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to find the LCM of two integers
int lcm(int a, int b) {
    return (a / gcd(a, b)) * b;
}

// Main function to solve the problem
void solve() {
    int q;
    cin >> q;
    while (q--) {
        string s, t;
        cin >> s >> t;

        int len_s = s.length();
        int len_t = t.length();
        int lcm_length = lcm(len_s, len_t);

        // Construct strings to match the LCM length
        string repeated_s = "";
        for (int i = 0; i < lcm_length / len_s; ++i) {
            repeated_s += s;
        }

        string repeated_t = "";
        for (int i = 0; i < lcm_length / len_t; ++i) {
            repeated_t += t;
        }

        // Check if the LCM string is consistent for both s and t
        if (repeated_s == repeated_t) {
            cout << repeated_s << endl;
        } else {
            cout << -1 << endl;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    solve();
    return 0;
}
 