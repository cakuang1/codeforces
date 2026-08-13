#include <iostream>
using namespace std;

const long long mod = 998244353;
long long N;
long long K;
long long L;
long long Answer;

int main() {
	// Step 1. Input
	cin >> N >> K >> L;

	// Step 2. Calculation
	Answer = 1;
	for (int i = 1; i <= N; i++) {
		if (i <= N - K) {
			Answer *= max(0LL, L + 1 - i);
		}
		else {
			Answer *= max(0LL, L - (N - K));
		}
		Answer %= mod; // Take mod every time to prevent overflow
	}

	// Step 3. Output
	cout << Answer << endl;
	return 0;
}
// wdho