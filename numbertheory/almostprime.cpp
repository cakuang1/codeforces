#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;

    // Step 1: Create an array to count the number of distinct prime divisors
    vector<int> primeDivisorCount(n + 1, 0);

    // Step 2: Use sieve to count prime divisors for each number
    for (int i = 2; i <= n; ++i) {
        if (primeDivisorCount[i] == 0) {  // i is a prime number
            for (int j = i; j <= n; j += i) {
                primeDivisorCount[j]++;
            }
        }
    }

    // Step 3: Count numbers with exactly 2 distinct prime divisors
    int almostPrimeCount = 0;
    for (int i = 2; i <= n; ++i) {
        if (primeDivisorCount[i] == 2) {
            almostPrimeCount++;
        }
    }

    // Output the result
    cout << almostPrimeCount << endl;

    return 0;
}
