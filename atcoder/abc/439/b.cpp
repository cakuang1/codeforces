#include <bits/stdc++.h>
using namespace std;

static int nxt(int x) {
    int s = 0;
    while (x > 0) {
        int d = x % 10;
        s += d * d;
        x /= 10;
    }
    return s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    // N <= 2026, so after one step it's <= 4 * 9^2 = 324.
    // We can just detect cycles with a visited array on [0..324].
    vector<char> seen(325, 0);

    int x = N;
    while (true) {
        if (x == 1) {
            cout << "Yes\n";
            return 0;
        }
        if (x <= 324 && seen[x]) {
            cout << "No\n";
            return 0;
        }
        if (x <= 324) seen[x] = 1;
        x = nxt(x);
    }
}
