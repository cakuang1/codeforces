#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, b;
    cin >> a >> b;

    if (a + b == 9 || a - b == 9 || a * b == 9 ||
        (b != 0 && a / b == 9)) {
        cout << "Nine\n";
    } else {
        cout << "Nein\n";
    }
}