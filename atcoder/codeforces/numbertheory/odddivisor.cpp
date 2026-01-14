#include <iostream>
using namespace std;

// Function to check if a number is a power of 2
bool isPowerOfTwo(long long n) {
    return (n & (n - 1)) == 0;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        long long n;
        cin >> n;
        // Check if the number has any odd divisor greater than 1
        if (n > 1 && !isPowerOfTwo(n)) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}
