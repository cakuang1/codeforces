#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int P, Q, X, Y;
    cin >> P >> Q >> X >> Y;

    if (0 <= X - P && X - P < 100 && 0 <= Y - Q && Y - Q < 100) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
    return 0;
}
