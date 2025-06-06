#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        // (1) If n is even, we can simply pair up adjacent buns,
        //     e.g. output: 1,1, 2,2, 3,3, ..., n/2,n/2
        if (n % 2 == 0) {
            for (int i = 1; i <= n/2; i++) {
                cout << i << " " << i << " ";
            }
            cout << "\n";
            continue;
        }

        // (2) If n is odd but < 27, no solution.
        if (n < 27) {
            cout << "-1\n";
            continue;
        }

        // (3) n is odd and n >= 27.
        //     First print a hard‐coded length‐27 arrangement:
        //
        // Indices:  1  2 3  4 5  6 7  8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27
        // Labels:   1, 3,3, 4,4, 5,5, 6,6, 1,  2,  8, 8,  9, 9,  10,10, 11,11, 12,12, 13,13, 14,14,  1,  2
        static const int seed27[27] = {
             1,  3,  3,  4,  4,  5,  5,  6,  6,
             1,  2,  8,  8,  9,  9, 10, 10, 11,
            11, 12, 12, 13, 13, 14, 14,  1,  2
        };
        for (int i = 0; i < 27; i++) {
            cout << seed27[i] << " ";
        }

        // Next, append the remaining (n - 27) buns as adjacent pairs with new colors:
        // Start nextColor = 15 (since we used up through 14 already).
        int nextColor = 15;
        int pairsToAdd = (n - 27) / 2;
        for (int i = 0; i < pairsToAdd; i++) {
            // each new pair is distance 1 apart, which is a square (1^2)
            cout << nextColor << " " << nextColor << " ";
            nextColor++;
        }

        // Done with this test case
        cout << "\n";
    }

    return 0;
}
