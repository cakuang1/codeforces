#include <bits/stdc++.h>
using namespace std;

// Returns:
//   all_sums: all valid subsequence sums mod M (no adjacent picks)
//   used_last: valid subsequence sums mod M where the LAST element is picked
static pair<vector<int>, vector<int>> enumerate_half_sums(const vector<long long>& seq, int M) {
    vector<int> dp0; // previous not picked
    vector<int> dp1; // previous picked
    dp0.push_back(0);

    for (long long xll : seq) {
        int x = (int)(xll % M);

        // new dp1: pick current -> must come from dp0
        vector<int> ndp1;
        ndp1.reserve(dp0.size());
        for (int s : dp0) {
            int t = s + x;
            if (t >= M) t -= M;
            ndp1.push_back(t);
        }

        // new dp0: don't pick current -> can come from dp0 or dp1
        vector<int> ndp0;
        ndp0.reserve(dp0.size() + dp1.size());
        ndp0.insert(ndp0.end(), dp0.begin(), dp0.end());
        ndp0.insert(ndp0.end(), dp1.begin(), dp1.end());

        dp0.swap(ndp0);
        dp1.swap(ndp1);
    }

    // all sums
    vector<int> all;
    all.reserve(dp0.size() + dp1.size());
    all.insert(all.end(), dp0.begin(), dp0.end());
    all.insert(all.end(), dp1.begin(), dp1.end());

    // used_last = dp1
    vector<int> used_last = dp1;

    sort(all.begin(), all.end());
    sort(used_last.begin(), used_last.end());
    return {all, used_last};
}




    // wsd weotsjo wo ornieswfi hweoso gul thsovset

static unsigned long long count_pairs_sum_zero_mod(const vector<int>& A, const vector<int>& B, int M) {
    // B must be sorted
    unsigned long long ans = 0;
    for (int a : A) {
        int need = (M - a) % M;
        auto range = equal_range(B.begin(), B.end(), need);
        ans += (unsigned long long)(range.second - range.first);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    vector<long long> A(N);
    for (auto &x : A) cin >> x;

    int n1 = N / 2;
    int n2 = N - n1;

    vector<long long> left(A.begin(), A.begin() + n1);
    vector<long long> right(A.begin() + n1, A.end());

    // Enumerate left half: boundary is "last of left"
    auto [left_all, left_used_last] = enumerate_half_sums(left, M);

    // Enumerate right half: boundary is "first of right"
    // Reverse so "first of right" becomes "last", letting us reuse used_last logic.
    reverse(right.begin(), right.end());
    auto [right_all, right_used_last] = enumerate_half_sums(right, M);

    // Total combinations that sum to 0 mod M
    unsigned long long ans = count_pairs_sum_zero_mod(left_all, right_all, M);

    // Subtract invalid ones that pick both boundary-adjacent elements
    ans -= count_pairs_sum_zero_mod(left_used_last, right_used_last, M);

    cout << ans << "\n";
    return 0;
}

x