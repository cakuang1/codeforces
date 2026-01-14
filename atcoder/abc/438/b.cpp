#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    string S, T;
    cin >> N >> M >> S >> T;

    const int INF = 1e9;
    int ans = INF;

    // sliding window start
    for (int i = 0; i + M <= N; i++) {
        int cost = 0;
        for (int j = 0; j < M; j++) {
            int s = S[i + j] - '0';
            int t = T[j] - '0';
            cost += (s - t + 10) % 10;
        }
        ans = min(ans, cost);
    }

    cout << ans << '\n';
    return 0;
}
