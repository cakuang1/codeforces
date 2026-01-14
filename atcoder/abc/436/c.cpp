#include <bits/stdc++.h>
using namespace std;

struct PairHash {
    size_t operator()(const pair<long long, long long>& p) const {
        // A simple but effective hash for pairs
        return (p.first << 32) ^ p.second;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long N;
    int M;
    cin >> N >> M;

    unordered_set<pair<long long, long long>, PairHash> occupied;
    occupied.reserve(4LL * M);
    occupied.max_load_factor(0.7);

    long long answer = 0;

    for (int i = 0; i < M; i++) {
        long long R, C;
        cin >> R >> C;

        // The 4 cells of the 2x2 block
        pair<long long, long long> cells[4] = {
            {R, C},
            {R + 1, C},
            {R, C + 1},
            {R + 1, C + 1}
        };

        bool overlap = false;
        for (auto &cell : cells) {
            if (occupied.count(cell)) {
                overlap = true;
                break;
            }
        }

        if (!overlap) {
            for (auto &cell : cells) {
                occupied.insert(cell);
            }
            answer++;
        }
    }

    cout << answer << "\n";
    return 0;
}
