#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<vector<int>> cnt(3, vector<int>(7, 0));

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 6; j++) {
            int x;
            cin >> x;
            cnt[i][x]++;
        }
    }

    vector<int> p = {4, 5, 6};

    double good = 0;

    do {
        good += cnt[0][p[0]] * cnt[1][p[1]] * cnt[2][p[2]];
    } while (next_permutation(p.begin(), p.end()));

    cout << fixed << setprecision(10) << good / 216.0 << '\n';

    return 0;
}