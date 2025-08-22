// C++ Code
#include <bits/stdc++.h>
using namespace std;

// Macro to check if a coordinate is valid in the grid
#define isValid(a) (a >= 0 && a < 7 ? 1 : 0)

// Direction constants
#define right 0
#define left 1
#define down 2
#define up 3

// Direction vectors for right, left, down, and up
int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { 1, -1, 0, 0 };

// The path description string
string str;
int vis[7][7];

// Function to count the number of paths that match the
// description
int countPaths(int x, int y, int pos)
{
    // If we have processed all characters in the string and
    // we are at the lower-left square, return 1
    if (pos == (int)str.length())
        return (x == 6 && y == 0);

    // If we have reached the lower-left square before
    // processing all characters, return 0
    if (x == 6 && y == 0)
        return 0;

    // If the current cell is already visited, return 0
    if (vis[x][y])
        return 0;

    // Array to keep track of the visited status of the
    // neighboring cells
    vector<bool> visited(4, -1);
    for (int k = 0; k < 4; k++)
        if (isValid(x + dx[k]) && isValid(y + dy[k]))
            visited[k] = vis[x + dx[k]][y + dy[k]];

    // If we are at a position such that the up and down
    // squares are unvisited and the left and right squares
    // are visited return 0
    if (!visited[down] && !visited[up] && visited[right]
        && visited[left])
        return 0;

    // If we are at a position such that the left and right
    // squares are unvisited and the up and down squares are
    // visited return 0
    if (!visited[right] && !visited[left] && visited[down]
        && visited[up])
        return 0;

    // If we are at a position such that the upper-right
    // diagonal square is visited and the up and right
    // squares are unvisited return 0
    if (isValid(x - 1) && isValid(y + 1)
        && vis[x - 1][y + 1] == 1)
        if (!visited[right] && !visited[up])
            return 0;

    // If we are at a position such that the lower-right
    // diagonal square is visited and the down and right
    // squares are unvisited return 0
    if (isValid(x + 1) && isValid(y + 1)
        && vis[x + 1][y + 1] == 1)
        if (!visited[right] && !visited[down])
            return 0;

    // If we are at a position such that the upper-left
    // diagonal square is visited and the up and left
    // squares are unvisited return 0
    if (isValid(x - 1) && isValid(y - 1)
        && vis[x - 1][y - 1] == 1)
        if (!visited[left] && !visited[up])
            return 0;

    // If we are at a position such that the lower-left diagonal
    // square is visited and the down and right squares are
    // unvisited return 0
    if (isValid(x + 1) && isValid(y - 1)
        && vis[x + 1][y - 1] == 1)
        if (!visited[left] && !visited[down])
            return 0;

    // Mark the current cell as visited
    vis[x][y] = 1;

    // Variable to store the number of paths
    int numberOfPaths = 0;

    // If the current character is '?', try all four
    // directions
    if (str[pos] == '?') {
        for (int k = 0; k < 4; k++)
            if (isValid(x + dx[k]) && isValid(y + dy[k]))
                numberOfPaths += countPaths(
                    x + dx[k], y + dy[k], pos + 1);
    }

    // If the current character is a direction, go in that
    // direction
    else if (str[pos] == 'R' && y + 1 < 7)
        numberOfPaths += countPaths(x, y + 1, pos + 1);
    else if (str[pos] == 'L' && y - 1 >= 0)
        numberOfPaths += countPaths(x, y - 1, pos + 1);
    else if (str[pos] == 'U' && x - 1 >= 0)
        numberOfPaths += countPaths(x - 1, y, pos + 1);
    else if (str[pos] == 'D' && x + 1 < 7)
        numberOfPaths += countPaths(x + 1, y, pos + 1);

    // Unmark the current cell
    vis[x][y] = 0;

    // Return the number of paths
    return numberOfPaths;
}

// Driver Code
int main()
{
    cin >> str;
    cout << countPaths(0, 0, 0) << endl;
}
