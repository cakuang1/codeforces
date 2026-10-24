#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<string> S(N);
    for (string& s : S) cin >> s;

    vector<int> votes(N, 0);

    while (M--) {
        string t;
        cin >> t;

        int exact = -1;
        int near = -1;
        int nearCount = 0;

        for (int i = 0; i < N; ++i) {
            if (S[i].size() != t.size()) continue;

            int diff = 0;
            for (int k = 0; k < (int)t.size(); ++k) {
                diff += (S[i][k] != t[k]);
            }

            if (diff == 0) {
                exact = i;
            } else if (diff == 1) {
                near = i;
                ++nearCount;
            }
        }

        if (exact != -1) {
            ++votes[exact];
        } else if (nearCount == 1) {
            ++votes[near];
        }
    }

    for (int v : votes) cout << v << '\n';
}