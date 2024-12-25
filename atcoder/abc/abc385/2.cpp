#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int h, w, X, Y;
    cin >> h >> w >> X >> Y;

    // Convert 1-based coordinates to 0-based
    int x = X - 1, y = Y - 1;

    vector<vector<char>> grid(h, vector<char>(w));
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            cin >> grid[i][j];
        }
    }

    string s;
    cin >> s;

    // Track visited houses
    set<pair<int, int>> visitedHouses;

    // Initial cell
    if (grid[x][y] == '@') {
        visitedHouses.insert({x, y});
    }

    for (char c : s) {
        int newx = x, newy = y;

        if (c == 'U') {
            newx = x - 1;  // Move up
        } else if (c == 'D') {
            newx = x + 1;  // Move down
        } else if (c == 'L') {
            newy = y - 1;  // Move left
        } else if (c == 'R') {
            newy = y + 1;  // Move right
        }

        // Check bounds and if the cell is passable
        if (newx >= 0 && newx < h && newy >= 0 && newy < w && grid[newx][newy] != '#') {
            x = newx;
            y = newy;

            // Mark house if visited
            if (grid[x][y] == '@') {
                visitedHouses.insert({x, y});
            }
        }
    }

    // Output final position and distinct houses visited
    cout << x + 1 << " " << y + 1 << " " << visitedHouses.size() << endl;

    return 0;
}
