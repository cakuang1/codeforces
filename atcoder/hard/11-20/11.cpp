#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// Function to calculate GCD
long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int countDistinctPrimes(long long n) {
    int count = 0;
    if (n % 2 == 0) {
        count++;
        while (n % 2 == 0) {
            n /= 2;
        }
    }
    for (long long i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            count++;
            while (n % i == 0) {
                n /= i;
            }
        }
    }
    if (n > 2) {
        count++;
    }

    return count;
}

int main() {
    long long A, B;
    cin >> A >> B;

    long long g = gcd(A, B);
    int result = countDistinctPrimes(g);

    cout << result + 1<< endl;

    return 0;
}
