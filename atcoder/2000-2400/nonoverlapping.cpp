#include <iostream>
#include <vector>
#include <ranges>
#include <numeric>
#include <algorithm>

int main() {
    using namespace std;
    static constexpr auto chmax{[](auto &&x, const auto &y) {
        if (x < y) x = y;
        return x;
    }};
    static constexpr auto max{[](const auto &x, const auto &y) {
        if (x < y) return y;
        return x;
    }};

    unsigned N, M;
    cin >> N >> M;

    // sum[i][j] := the sum of the M x M square whose top-left cell is (i, j)
    auto sum{[N, M] {
        vector A(N + 1, vector<unsigned long>(N + 1));
        for (auto &&row: A | views::take(N))
            for (auto &&a: row | views::take(N))
                cin >> a;

        // Let A[i][j] ← ∑_{i≤k,j≤l} A[k][l]
        for (unsigned row_index{N}; auto &&row : A | views::reverse){
        inclusive_scan(rbegin(row), rend(row), rbegin(row), plus<>{});
        if (row_index < N)
            ranges::transform(row, A[row_index + 1], begin(row), plus<>{});
        --row_index;
    }

        // sum[i][j] = A[i][j] - A[i+M][j] - A[i][j+M] + A[i+M][j+M]
        vector sum(N - M + 1, vector<unsigned long>(N - M + 1));
        for (unsigned i{}; i <= N - M; ++i)
            for (unsigned j{}; j <= N - M; ++j)
                sum[i][j] = A[i][j] - A[i + M][j] - A[i][j + M] + A[i + M][j + M];
        return sum;
    }()};

    // cumulative max of sum[i][j] from the top-left
    // m[i][j] = max_{k≤i,l≤j} sum[k][l]
    const auto max_UL{[](auto cells) {
        for (unsigned row_index{}; auto &&row : cells){
        inclusive_scan(begin(row), end(row), begin(row), max);
        if (row_index)
            ranges::transform(row, cells[row_index - 1], begin(row), max);
        ++row_index;
    }
        return cells;
    }};

    // flip the board horizontally
    const auto h_flip{[](auto &&cells) {
        for (auto &&row: cells)
            ranges::reverse(row);
        return cells;
    }};
    // flip the board vertically
    const auto v_flip{[](auto &&cells) {
        ranges::reverse(cells);
        return cells;
    }};

    const auto upper_left{max_UL(sum)}; // cumulative max from the top-left
    h_flip(sum); // flip horizontally
    const auto upper_right{h_flip(max_UL(sum))}; // cumulative max from the top-right
    v_flip(sum); // flip vertically
    const auto lower_right{h_flip(v_flip(max_UL(sum)))}; // cumulative max from the bottom-right
    h_flip(sum); // flip vertically
    const auto lower_left{v_flip(max_UL(sum))}; // cumulative max from the bottom-left
    v_flip(sum); // return to the original state

    unsigned long ans{};

    // Fix a square
    for (unsigned i{}; i < N - M + 1; ++i)
        for (unsigned j{}; j < N - M + 1; ++j) {
            if (M <= i && i + M < N - M + 1) // three squares arranged vertically; fix the center square
                chmax(ans, upper_left[i - M].back() + sum[i][j] + lower_right[i + M].front());
            if (M <= j && j + M < N - M + 1) // three squares arranged horizontally; fix the center square
                chmax(ans, upper_left.back()[j - M] + sum[i][j] + lower_right.front()[j + M]);
            if (M <= i) { // T-shaped
                if (j + M < N - M + 1) // bottom left
                    chmax(ans, upper_left[i - M].back() + lower_right[i][j + M] + sum[i][j]);
                if (M <= j) // bottom right
                    chmax(ans, upper_left[i - M].back() + lower_left[i][j - M] + sum[i][j]);
            }
            if (M <= j) { // ト-shaped
                if (i + M < N - M + 1) // bottom right
                    chmax(ans, lower_left.front()[j - M] + lower_right[i + M][j] + sum[i][j]);
                if (M <= i) // top right
                    chmax(ans, lower_left.front()[j - M] + upper_right[i - M][j] + sum[i][j]);
            }
            if (i + M < N - M + 1) { // 亠 -shaped
                if (j + M < N - M + 1) // top-left
                    chmax(ans, lower_right[i + M].front() + upper_right[i][j + M] + sum[i][j]);
                if (M <= j) // top-right
                    chmax(ans, lower_right[i + M].front() + upper_left[i][j - M] + sum[i][j]);

            }
            if (j + M < N - M + 1) { // ㅓ -shaped
                if (i + M < N - M + 1) // top-left
                    chmax(ans, upper_right.back()[j + M] + lower_left[i + M][j] + sum[i][j]);
                if (M <= i) // bottom-left
                    chmax(ans, upper_right.back()[j + M] + upper_left[i - M][j] + sum[i][j]);
            }
        }

    cout << ans << endl;
    return 0;
}
