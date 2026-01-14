#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int N;
        string S;
        cin >> N >> S;

        int M = 1 << N;
        vector<char> safe(M, 0);
        safe[0] = 1; // empty bottle is always OK
        for (int mask = 1; mask < M; mask++) {
            safe[mask] = (S[mask - 1] == '0');
        }

        vector<char> vis(M, 0);
        queue<int> q;
        vis[0] = 1;
        q.push(0);

        while (!q.empty()) {
            int mask = q.front(); q.pop();
            if (mask == M - 1) break;

            int rem = (~mask) & (M - 1); // bits not yet poured
            while (rem) {
                int b = __builtin_ctz(rem);
                rem &= rem - 1;
                int nmask = mask | (1 << b);
                if (!vis[nmask] && safe[nmask]) {
                    vis[nmask] = 1;
                    q.push(nmask);
                }
            }
        }

        cout << (vis[M - 1] ? "Yes\n" : "No\n");
    }
    return 0;
}
