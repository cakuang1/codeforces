#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

int64 pow10(int e) {
    int64 x = 1;
    while (e--) x *= 10;
    return x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int a1, a2, a3;
        cin >> a1 >> a2 >> a3;

        bool swapped = false;

        if (a1 > a2) {
            swap(a1, a2);
            swapped = true;
        }

        if (a3 < a2 || a3 > a1 + a2) {
            cout << "No\n";
            continue;
        }

        int64 x1, x2;

        if (a3 == a1 + a2) {
            x1 = 8 * pow10(a1 - 1) + 1;
            x2 = 8 * pow10(a2 - 1);
        } else {
            x1 = pow10(a1 - 1);
            x2 = pow10(a2) - pow10(a1 + a2 - a3 - 1);
        }

        if (swapped) {
            swap(x1, x2);
        }

        cout << "Yes\n";
        cout << x1 << ' ' << x2 << '\n';
    }

    return 0;
}

// werwjopsfrw


// wconsts sosofwwn irhsirw

// wwrwth so sLCM wes maks wwirw
 w