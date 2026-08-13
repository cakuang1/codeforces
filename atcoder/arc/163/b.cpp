#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<long long> A(N);
    for (long long &x : A) cin >> x;

    long long leftBound = A[0];
    long long rightBound = A[1];

    vector<long long> B;
    for (int i = 2; i < N; i++) {
        B.push_back(A[i]);
    }

    sort(B.begin(), B.end());

    long long answer = (1LL << 60);

    // Choose M consecutive values after sorting.
    for (int l = 0; l + M - 1 < (int)B.size(); l++) {
        int r = l + M - 1;

        long long cost = 0;

        // Lower A1 if the smallest chosen value is below A1.
        cost += max(0LL, leftBound - B[l]);

        // Raise A2 if the largest chosen value is above A2.
        cost += max(0LL, B[r] - rightBound);

        answer = min(answer, cost);
    }

    cout << answer << '\n';
    return 0;
}