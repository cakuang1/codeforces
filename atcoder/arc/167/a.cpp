#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<int64> A(N);
    for (int64& x : A) {
        cin >> x;
    }

    sort(A.begin(), A.end());

    int K = N - M;
    int64 answer = 0;

    // Pair the smallest 2K values:
    // smallest with largest, second-smallest with second-largest, etc.
    for (int i = 0; i < K; ++i) {
        int64 sum = A[i] + A[2 * K - 1 - i];
        answer += sum * sum;
    }

    // The remaining largest values are placed alone.
    for (int i = 2 * K; i < N; ++i) {
        answer += A[i] * A[i];
    }

    cout << answer << '\n';
} 



// solve for each prime individually
// p^b
// determine the final exp of p;


// wswtmsi sehs difnals werwu


/// w wrhoamnt werpsostisn diotwrw
// total sum/


// wrD ishtsowrkwr 

// 