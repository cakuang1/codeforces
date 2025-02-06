#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    long long K; // K can be large (up to 10^9)
    cin >> s >> K;
    
    int n = s.length();

    // Step 1: Try converting letters to 'a' greedily
    for (int i = 0; i < n; i++) {
        if (K == 0) break; // No more operations left

        int steps = ('z' - s[i] + 1) % 26; // Steps to reach 'a'

        if (steps <= K) { // If we have enough moves
            s[i] = 'a';
            K -= steps;
        }
    }

    // Step 2: Apply remaining K to the last character
    if (K > 0) {
        s[n - 1] = 'a' + ((s[n - 1] - 'a' + K) % 26);
    }

    cout << s << endl;
    return 0;
}
