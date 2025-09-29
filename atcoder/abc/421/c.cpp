#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    string S;
    cin >> n >> S;  // <-- read N and S properly

    vector<int> X; // positions of A's
    for (int i = 0; i < (int)S.size(); i++) {
        if (S[i] == 'A') X.push_back(i + 1); // 1-indexed
    }



    long long cost1 = 0, cost2 = 0;
    for (int k = 0; k < n; k++) {
        cost1 += llabs(X[k] - (2 * k + 1)); // odd positions
        cost2 += llabs(X[k] - (2 * (k + 1))); // even positions
    }

    cout << min(cost1, cost2) << "\n";
}

// d oeshtww