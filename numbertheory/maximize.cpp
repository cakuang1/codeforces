#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int t;
    cin >> t;
    
    while (t--) {
        int x;
        cin >> x;
        
        int max_result = 0;
        int best_y = 1;
        
        for (int y = 1; y < x; ++y) {
            int current_value = __gcd(x, y) + y;
            if (current_value > max_result) {
                max_result = current_value;
                best_y = y;
            }
        }
        
        cout << best_y << endl;
    }
    
    return 0;
}
 