#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, k;
    cin >> n >> k;
    
    vector<int> A(n);
    for (int i = 0; i < n; i++) {
        cin >> A[i]; // Read allowed moves
    }

    vector<bool> dp(k + 1, false); // dp[i] = true if Taro wins with i stones

    for (int stones = 1; stones <= k; stones++) {
        for (int x : A) {
            if (stones >= x && !dp[stones - x]) {
                dp[stones] = true;
                break;
            }
        }
    }

    cout << (dp[k] ? "First" : "Second") << endl;
    return 0;
}
