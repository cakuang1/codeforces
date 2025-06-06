#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    using namespace std;
    unsigned H, W;
    cin >> H >> W;
    vector A(H, vector<unsigned long>(W));
    for (auto&& row : A)
        for (auto&& a : row)
            cin >> a;

    // Use an (HW)-bit integer to manage the cells occupied by dominoes
    vector<unsigned> possible_domino{0}; // Initially, there is an empty grid

    const unsigned domino_vertical = (1U << W) + 1, domino_horizontal = 3;

    for (unsigned i = 0, bit = 0; i < H; ++i)
        for (unsigned j = 0; j < W; ++j, ++bit) { // For each cell
            vector<unsigned> tmp;
            for (const auto b : possible_domino) {
                // If a horizontal domino can be placed, add such a placement
                if (j + 1 < W && !(b & domino_horizontal << bit))
                    tmp.emplace_back(b | domino_horizontal << bit);
                // If a vertical domino can be placed, add such a placement
                if (i + 1 < H && !(b & domino_vertical << bit))
                    tmp.emplace_back(b | domino_vertical << bit);
            }
            ranges::move(tmp, back_inserter(possible_domino));
        }

    unsigned long ans = 0;
    for (const auto b : possible_domino) { // For each placement
        unsigned long now = 0;
        for (unsigned i = 0, bit = 0; i < H; ++i)
            for (unsigned j = 0; j < W; ++j, ++bit)
                if (1 & ~b >> bit) // inspect each cell not covered by a domino
                    now ^= A[i][j]; // to find the total XOR
        ans = max(ans, now); // Update if it is larger
    }

    cout << ans << endl;
    return 0;
}
