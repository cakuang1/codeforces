#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long x, y, z;
    cin >> x >> y >> z;

    long long diff = x - y * z;

    if (diff >= 0 && diff % (z - 1) == 0) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
    return 0;
}
//wf osths wriwr kwr d werow