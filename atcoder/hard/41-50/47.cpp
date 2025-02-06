#include <iostream>
#include <queue>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int k;
    cin >> k;

    queue<long long> q;

    // Initialize queue with single-digit lunlun numbers
    for (int i = 1; i <= 9; i++) {
        q.push(i);
    }

    long long result = 0;

    // Perform BFS to find the k-th lunlun number
    while (k--) {
        result = q.front();
        q.pop();

        int last_digit = result % 10; // Extract last digit

        // Generate new Lunlun numbers based on last digit
        if (last_digit > 0) {
            q.push(result * 10 + (last_digit - 1));
        }
        q.push(result * 10 + last_digit);
        if (last_digit < 9) {
            q.push(result * 10 + (last_digit + 1));
        }
    }

    cout << result << endl;
    return 0;
}
