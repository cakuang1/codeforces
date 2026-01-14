#include <bits/stdc++.h>
using namespace std;

long long digit_sum(long long x) {
    long long s = 0;
    while (x > 0) {
        s += x % 10;
        x /= 10;
    }
    return s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<long long> A(N + 1);
    A[0] = 1;

    long long pref = 0; // sum of digit sums of A[0..i-1]

    for (int i = 1; i <= N; i++) {
        pref += digit_sum(A[i - 1]); // add f(A[i-1])
        A[i] = pref;                // A[i] = sum_{j=0}^{i-1} f(A[j])
    }

    cout << A[N] << "\n";
    return 0;
}

/