#include <bits/stdc++.h>
using namespace std;

// check if integer a has digit '7' in its decimal form
bool has7(long long a) {
    while (a > 0) {
        if ((a % 10) == 7) return true;
        a /= 10;
    }
    return false;
}

int solve_one(long long n) {
    // List of all-9 numbers up to 10 digits
    static long long all9[10] = {
        9LL,
        99LL,
        999LL,
        9999LL,
        99999LL,
        999999LL,
        9999999LL,
        99999999LL,
        999999999LL,
        9999999999LL
    };

    int best = INT_MAX;
    for (int i = 0; i < 10; i++) {
        long long x = all9[i];
        long long cur = n;
        int steps = 0;
        // keep adding x until we see a '7'
        while (!has7(cur)) {
            cur += x;
            steps++;
            // (In practice, steps will be ≤ 10–12 here, because each digit
            //  cycles mod 10.)
        }
        best = min(best, steps);
    }
    return best;
}

// how to see this and hwy does thiwe
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        long long n;
        cin >> n;
        // If n already has a '7', 0 moves are needed
        if (has7(n)) {
            cout << 0 << "\n";
        } else {
            cout << solve_one(n) << "\n";
        }
    }
    return 0;
}
