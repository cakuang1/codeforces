#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string S;
    cin >> S;

    int n = S.size();
    int limit = 1;
    for (int i = 0; i < n; ++i) limit *= 10;

    // Sieve: prime[v] tells us whether v is prime.
    vector<bool> prime(limit, true);
    prime[0] = prime[1] = false;

    for (int p = 2; 1LL * p * p < limit; ++p) {
        if (!prime[p]) continue;

        for (int v = p * p; v < limit; v += p) {
            prime[v] = false;
        }
    }

    // Only examine numbers with exactly n digits.
    int lower = limit / 10;

    for (int p = max(2, lower); p < limit; ++p) {
        if (!prime[p]) continue;

        string T = to_string(p);
        bool matches = true;

        for (int i = 0; i < n && matches; ++i) {
            for (int j = i + 1; j < n; ++j) {
                // Same letters iff same digits.
                if ((S[i] == S[j]) != (T[i] == T[j])) {
                    matches = false;
                    break;
                }
            }
        }

        if (matches) {
            cout << p << '\n';
            return 0;
        }
    }

    cout << -1 << '\n';
    return 0;
}

// webuwetw ersdo weri wer
w