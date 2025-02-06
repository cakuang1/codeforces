#include <iostream>
#include <vector>

using namespace std;

void baseNegativeTwo(int N) {
    if (N == 0) {
        cout << "0" << endl;
        return;
    }

    vector<int> result;
    
    while (N != 0) {
        // Compute remainder (0 or 1)
        int remainder = N % 2;
        
        // Ensure remainder is non-negative (important for negative numbers)
        if (remainder < 0) remainder += 2;

        // Store the remainder as the current digit
        result.push_back(remainder);

        // Update N by subtracting remainder and dividing by -2
        N = (N - remainder) / -2;
    }

    // Print the result in reverse order (most significant bit first)
    for (int i = result.size() - 1; i >= 0; i--) {
        cout << result[i];
    }
    cout << endl;
}

int main() {
    int N;
    cin >> N;  // Read input
    baseNegativeTwo(N);
    return 0;
}
