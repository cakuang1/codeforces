#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <stack>
#include <deque>
#include <bitset>
#include <limits>

// single number one of
using namespace std;

int main() {
    int x, y; 
    // Loop through the 5x5 matrix to find the position of the number 1
    for (int r = 1; r <= 5; r++) {
        for (int c = 1; c <= 5; c++) {
            int value;
            cin >> value;
            if (value == 1) {
                // Assign the position of the number 1 to x and y
                x = r;
                y = c;
            }
        }
    }
    
    // Calculate the Manhattan distance to the center (3, 3)
    int res = abs(3 - x) + abs(3 - y);

    // Output the result
    cout << res << endl;

    return 0;
}