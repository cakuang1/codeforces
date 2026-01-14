#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<string> S(N);
    for (int i = 0; i < N; i++) cin >> S[i];

    unordered_set<string> seen;
    seen.reserve((size_t)N * (N - 1) * 2);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j) continue;
            seen.insert(S[i] + S[j]);
        }
    }

    cout << seen.size() << "\n";
    return 0;
}
