#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <numeric>
#include <ranges>

int main() {
    using namespace std;
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    unsigned N;
    cin >> N;
    vector<array<unsigned, 3>> P(N);
    for (auto&& [p, a, b] : P)
        cin >> p >> a >> b;

    // Manage mood up to {max (P + A)}
    const auto M{ranges::max(P | views::transform([](const auto& p) { return p[0] + p[1]; }))};

    // dp[i][j] := the final mood value if the mood value right after receiving present i is j.
    vector dp(N + 1, vector<unsigned>(M + 1));

    // If the mood after receiving all presents is j, then the final mood is j
    iota(begin(dp.back()), end(dp.back()), 0);

    for (unsigned i = N; i--; ) {
        const auto& [p, a, b] = P[i];
        for (unsigned j = 0; j <= M; ++j)
            // +A if the current mood value is not greater than the present's value, and -B otherwise
            dp[i][j] = j <= p ? dp[i + 1][j + a] : dp[i + 1][j - min(j, b)];
    }

    // Find the cumulative sums to determine when the mood falls into the range when a large mood value is found.
    vector<unsigned> sum_B(N);
    ranges::copy(P | views::elements<2>, begin(sum_B));
    inclusive_scan(begin(sum_B), end(sum_B), begin(sum_B), plus{});

    // The final mood value when the initial mood is `x` (including offset)
    const auto access{[&dp, &sum_B, N, M](unsigned x) -> unsigned {
        // If it is within the range initially, then directly return the dp value
        if (x <= M)
            return dp[0][x];

        // If larger, keep descending for a while
        const auto need_down{ranges::lower_bound(sum_B, x - M)};
        // If descending N times is not sufficient, just descend N times
        if (need_down == end(sum_B))
            return x - sum_B.back();
        // Once reaching the range, return the DP value
        return dp[need_down - begin(sum_B) + 1][x - min(x, *need_down)];
    }};

    unsigned Q;
    cin >> Q;
    for (unsigned i = 0; i < Q; ++i) {
        unsigned x;
        cin >> x;
        cout << access(x) << '\n';
    }
    cout << flush;
    return 0;
}
// w dssthsi rweo sdnsi