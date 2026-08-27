#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;

        vector<int> A(N), B(N);

        for (int &x : A) cin >> x;
        for (int &x : B) cin >> x;

        int cntA = accumulate(A.begin(), A.end(), 0);
        int cntB = accumulate(B.begin(), B.end(), 0);

        // Total number of 1s is invariant.
        if (cntA != cntB) {
            cout << "No\n";
            continue;
        }

        // If there are 0 or at least 2 ones,
        // any arrangement with the same number of ones is reachable.
        if (cntA != 1) {
            cout << "Yes\n";
            continue;
        }

        /*
            Exactly one 1.

            There are three equivalence classes:

            1000...0       unique 1 at the left endpoint
            0...010...0    unique 1 somewhere internally
            0...0001       unique 1 at the right endpoint

            So we only need to check whether the endpoint status matches.
        */

        if (A[0] != B[0] || A[N - 1] != B[N - 1]) {
            cout << "No\n";
        } else {
            cout << "Yes\n";
        }
    }

    return 0;
}


// w