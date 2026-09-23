#include <bits/stdc++.h>
using namespace std;

vector<int> makeDiff(const vector<int>& s) {
    vector<int> d;

    for (int i = 0; i + 1 < (int)s.size(); i++) {
        d.push_back(s[i] != s[i + 1]);
    }

    return d;
}

// Number of 1s in each segment separated by 0s.
// For example: 11010111 -> [2, 1, 3].
vector<int> oneSegments(const vector<int>& d) {
    vector<int> cnt(1, 0);

    for (int x : d) {
        if (x == 0) {
            cnt.push_back(0);
        } else {
            cnt.back()++;
        }
    }

    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N, M;
        cin >> N >> M;

        vector<int> A(N), B(M);

        for (int& x : A) cin >> x;
        for (int& x : B) cin >> x;

        // The first and last original bits never change.
        if (A.front() != B.front() || A.back() != B.back()) {
            cout << "No\n";
            continue;
        }

        vector<int> DA = makeDiff(A);
        vector<int> DB = makeDiff(B);

        int zeroA = count(DA.begin(), DA.end(), 0);
        int zeroB = count(DB.begin(), DB.end(), 0);

        // 0 -> 101 preserves the number of zeroes in the difference string.
        if (zeroA != zeroB) {
            cout << "No\n";
            continue;
        }

        vector<int> CA = oneSegments(DA);
        vector<int> CB = oneSegments(DB);

        int S = (int)CA.size(); // zeroA + 1 segments

        /*
            dp[left] = can we process segments so far if the zero
            immediately to the left of the current segment was used
            `left` times?

            A zero is only worth trying 0, 1, or 2 times.
        */
        array<bool, 3> dp = {true, false, false};

        for (int i = 0; i < S; i++) {
            array<bool, 3> next = {false, false, false};

            for (int left = 0; left <= 2; left++) {
                if (!dp[left]) continue;

                // There is no zero to the right of the final segment.
                int maxRight = (i + 1 == S ? 0 : 2);

                for (int right = 0; right <= maxRight; right++) {
                    /*
                        Boundary operations contribute:
                          left + right

                        Remaining growth must be made by +2 operations
                        inside this segment.
                    */
                    int required = CB[i] - CA[i];
                    int boundaryGrowth = left + right;
                    int remaining = required - boundaryGrowth;

                    if (remaining < 0 || remaining % 2 != 0) {
                        continue;
                    }

                    /*
                        If we need a +2 internal operation, this segment
                        must contain at least one 1 after boundary growth.
                    */
                    if (remaining > 0 && CA[i] + boundaryGrowth == 0) {
                        continue;
                    }

                    next[right] = true;
                }
            }
            dp = next;
        }

        cout << (dp[0] ? "Yes\n" : "No\n");
    }
}


// 