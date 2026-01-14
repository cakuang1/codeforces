#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    using namespace std;
    unsigned T;
    cin >> T;
    for (unsigned t{}; t < T; ++t) cout << ([]{
        unsigned N;
        cin >> N;
        vector<long> A(N);
        for (auto&& a : A)
            cin >> a;

        // Print Yes if the values are all equal
        if (ranges::count(A, A[0]) == N)
            return true;

        // Print Yes if the sequence contains the initial value and its negation
        if (const auto p_cnt{ranges::count(A, A[0])}, n_cnt{ranges::count(A, -A[0])}; p_cnt + n_cnt == N && min(p_cnt, n_cnt) == N / 2)
            return true;

        // Sort by absolute values
        ranges::sort(A, greater{}, [](const auto a){ return abs(a); });

        // If the absolute value of the common ratio is 1, then it must form a geometric progression when sorted by absolute values
        for (unsigned i{}; i + 2 < N; ++i)
            if (A[i] * A[i + 2] != A[i + 1] * A[i + 1])
                return false;
        return true;
    }() ? "Yes" : "No") << endl;
    return 0;
}
