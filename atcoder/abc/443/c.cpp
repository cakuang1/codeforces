#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    long long T;
    cin >> N >> T;
    vector<long long> A(N);
    for (int i = 0; i < N; i++) cin >> A[i];

    long long ans = 0;
    long long cur = 0; // next time when chokutter is open
    int i = 0;

    while (cur < T) {
        while (i < N && A[i] < cur) i++; // passes while closed
        if (i == N || A[i] >= T) {
            ans += T - cur;
            break;
        }
        // A[i] is the first pass while open
        ans += A[i] - cur;   // watched until Aoki arrives
        cur = A[i] + 100;    // reopen time
        i++;                 // this Aoki event consumed
    }

    cout << ans << "\n";
    return 0;
}
