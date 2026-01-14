#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    // person 0 at coordinate 0
    set<long long> st;
    st.insert(0);

    unordered_map<long long,long long> nearest;
    nearest[0] = LLONG_MAX;   // no neighbors yet

    long long sum = 0; // defined as 0 initially by problem conventions

    for (int i = 1; i <= N; i++) {
        long long X;
        cin >> X;

        // Find neighbors
        auto it = st.lower_bound(X);

        long long L = -1, R = -1;

        if (it != st.begin()) {
            auto it2 = it; --it2;
            L = *it2;
        }
        if (it != st.end()) {
            R = *it;
        }

        // Remove old nearest values of L and R
        if (L != -1) sum -= nearest[L];
        if (R != -1) sum -= nearest[R];

        // Compute nearest[X]
        long long newX = LLONG_MAX;
        if (L != -1) newX = min(newX, X - L);
        if (R != -1) newX = min(newX, R - X);
        nearest[X] = newX;

        // Update L's nearest
        if (L != -1) {
            long long newL = LLONG_MAX;

            // left of L
            auto itL = st.lower_bound(L);
            if (itL != st.begin()) {
                auto it3 = itL; --it3;
                newL = min(newL, L - *it3);
            }
            // right of L is X
            newL = min(newL, X - L);

            nearest[L] = newL;
        }

        // Update R's nearest
        if (R != -1) {
            long long newR = LLONG_MAX;

            // left of R is X
            newR = min(newR, R - X);

            // right of R
            auto itR = st.upper_bound(R);
            if (itR != st.end()) {
                newR = min(newR, *itR - R);
            }

            nearest[R] = newR;
        }

        sum += nearest[X];
        if (L != -1) sum += nearest[L];
        if (R != -1) sum += nearest[R];

        // Insert X
        st.insert(X);

        cout << sum << "\n";
    }
    return 0;
}

// wsdfhist wrssigne wr