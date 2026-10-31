#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, h, k;
    cin >> n >> m >> h >> k;

    string s;
    cin >> s;

    set<pair<int, int>> items;

    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        items.insert({x, y});
    }

    int x = 0, y = 0;

    for (char c : s) {
        if (c == 'R') x++;
        if (c == 'L') x--;
        if (c == 'U') y++;
        if (c == 'D') y--;

        h--;

        if (h < 0) {
            cout << "No\n";
            return 0;
        }

        if (h < k && items.count({x, y})) {
            h = k;
            items.erase({x, y});
        }
    }

    cout << "Yes\n";
}