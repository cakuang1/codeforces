#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;

    vector<long long> add(N + 1, 0);
    vector<long long> need(N + 1, 0);

    // Find the worst local pressure on each boundary i -> i+1.
    for (int q = 0; q < Q; ++q) {
        int i;
        long long x;
        cin >> i >> x;

        add[i] += x;

        if (i < N) {
            need[i] = max(need[i], add[i] - add[i + 1]);
        }
    }

    // Transfer the local constraints left to right.
    // A1 is as small as possible.
    long long cur = 1;
    long long ans = cur;

    for (int i = 1; i < N; ++i) {
        cur += need[i] + 1;
        ans += cur;
    }

    cout << ans << '\n';
    return 0;
}