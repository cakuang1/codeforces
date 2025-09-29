#include <iostream>
#include <vector>
#include <limits>
#include <ranges>
int main() {
    using namespace std;
    unsigned N, M;
    cin >> N >> M;
    vector<unsigned> W(N);
    for (auto&& w : W)
        cin >> w;
    vector<pair<unsigned, unsigned>> edges(M);
    for (auto&& [u, v] : edges) {
        cin >> u >> v;
        --u;
        --v;
    }

    // 
    constexpr auto inf{numeric_limits<unsigned long>::max() / 2};
    // Initialize DP table with a sufficiently large value
    vector<unsigned long> dp(N, inf), prev(N, inf);
    dp[0] = 0;
    // Compute in descending order of the number of remaining tickets
    for (const auto i : views::iota(1U, N) | views::reverse) {
        swap(dp, prev);
        dp[0] = 0;
        for (const auto& [u, v] : edges) {
            dp[u] = min(dp[u], prev[v] + static_cast<unsigned long>(W[v]) * i);
            dp[v] = min(dp[v], prev[u] + static_cast<unsigned long>(W[u]) * i);
        }
    }
    for (const auto v : dp)
        cout << v << endl;
    return 0;
}