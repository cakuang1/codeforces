#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin >> s;

    // Step 1: Replace "BC" with "D"
    string t;
    for (int i = 0; i < s.length(); i++) {
        if (i + 1 < s.length() && s[i] == 'B' && s[i + 1] == 'C') {
            t += 'D';  // Replace "BC" with "D"
            i++;  // Skip the next character ('C')
        } else {
            t += s[i];
        }
    }

    // Step 2: Count inversions for AD -> DA swaps
    long long ans = 0;
    long long countA = 0;

    for (char c : t) {
        if (c == 'A') {
            countA++;  // Count number of 'A's seen so far
        } else if (c == 'D') {
            ans += countA;  // 'D' can swap with all previous 'A's
        } else {
            countA = 0;  // Reset when encountering 'B' or 'C' (obstacles)
        }
    }

    cout << ans << endl;
    return 0;
}
