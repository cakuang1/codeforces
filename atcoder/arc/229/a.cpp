#include <bits/stdc++.h>
using namespace std;

int main() {
    int X;
    cin >> X;

    vector<int> a;
    for (int i = 0; i < 25; i++) a.push_back(1); // A
    for (int i = 0; i < 25; i++) a.push_back(0); // C

    int remove = 625 - X;
    while (remove--) {
        for (int i = 0; i + 1 < 50; i++) {
            if (a[i] == 1 && a[i + 1] == 0) {
                swap(a[i], a[i + 1]);
                break;
            }
        }
    }

    for (int i = 0; i < 50; i++) {
        if (i) cout << 'R';
        cout << (a[i] ? 'A' : 'C');
    }
    cout << '\n';
}