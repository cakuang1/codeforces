#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    // N = 1 is a special case.
    if (N == 1) {
        cout << 1 << '\n';
        cout << 1 << '\n';
        return 0;
    }

    // All even numbers form a good set.
    cout << N / 2 << '\n';

    for (int x = 2; x <= N; x += 2) {
        cout << x << ' ';
    }
    cout << '\n';

    return 0;
}