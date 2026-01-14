#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // Step 1: Generate all ordinary numbers up to 10^9
    vector<long long> ordinaryNumbers;
    for (int digit = 1; digit <= 9; ++digit) {
        long long num = digit;
        while (num <= 1000000000) {
            ordinaryNumbers.push_back(num);
            num = num * 10 + digit; // Create the next number like 11, 111, 1111, etc.
        }
    }
    
    // Sort the ordinary numbers
    sort(ordinaryNumbers.begin(), ordinaryNumbers.end());

    // Step 2: Read input
    int t;
    cin >> t;
    while (t--) {
        long long n;
        cin >> n;

        // Step 3: Count how many ordinary numbers are <= n using upper_bound
        int count = upper_bound(ordinaryNumbers.begin(), ordinaryNumbers.end(), n) - ordinaryNumbers.begin();
        cout << count << endl;
    }

    return 0;
}
