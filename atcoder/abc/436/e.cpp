#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<int> P(N);
    for (int i = 0; i < N; i++) {
        cin >> P[i];
        --P[i]; // to 0-index
    }

    vector<char> vis(N, 0);
    long long ans = 0;

    for (int i = 0; i < N; i++) if (!vis[i]) {
        int v = i;
        int cnt = 0;
        while (!vis[v]) {
            vis[v] = 1;
            cnt++;
            v = P[v];
        }
        // This "cnt" is the cycle size (each component is a cycle for a permutation).
        ans += 1LL * cnt * (cnt - 1) / 2; // number of (i,j) pairs inside this cycle
    }

    cout << ans << "\n";
    return 0;
}

// wsd setso wrwe wrw we