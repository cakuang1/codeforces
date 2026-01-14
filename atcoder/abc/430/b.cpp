#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, M;
    cin >> N >> M;
    vector<string> S(N);
    for (int i = 0; i < N; i++) cin >> S[i];

    const uint64_t BASE = 1315423911ULL;
    set<uint64_t> seen;

    for (int i = 0; i + M <= N; i++) {
        for (int j = 0; j + M <= N; j++) {
            uint64_t h = 0;
            for (int x = 0; x < M; x++) {
                for (int y = 0; y < M; y++) {
                    int bit = (S[i+x][j+y] == '#');
                    h = h * BASE + bit;
                }
            }
            seen.insert(h);
        }
    }

    cout << seen.size() << endl;
}

// 2d rahashesr wr