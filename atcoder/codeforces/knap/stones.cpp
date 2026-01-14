#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, K;
    cin >> n >> K;
    vector<int> A(n);
    for (int i = 0; i < n; i++) cin >> A[i];

    vector<bool> dp(K+1, false);
    dp[0] = false; // 0 stones = losing position

    for (int x = 1; x <= K; x++) {
        for (int a : A) {
            if (a > x) break;
            if (!dp[x - a]) { // can move to losing position
                dp[x] = true;
                break;
            }
        }
    }

    if (dp[K]) cout << "First\n";
    else cout << "Second\n";
}

 



