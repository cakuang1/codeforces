#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> A(n);
    for (int i = 0; i < n; i++) 
        cin >> A[i];

    int m;
    cin >> m;
    vector<int> B(m);
    for (int j = 0; j < m; j++) 
        cin >> B[j];

            / 
    vector<int> dp(m, 0), parent(m, -1);

    // Fill dp
    for (int i = 0; i < n; i++) {
        int bestLen = 0, bestIdx = -1;
        for (int j = 0; j < m; j++) {
            if (A[i] == B[j]) {
                if (bestLen + 1 > dp[j]) {
                    dp[j] = bestLen + 1;
                    parent[j] = bestIdx;
                }
            }
            else if (B[j] < A[i]) {
                if (dp[j] > bestLen) {
                    bestLen = dp[j];
                    bestIdx = j;
                }
            }
        }
    }
    
    // detemrin w
        
    int length = 0, end = -1;
    for (int j = 0; j < m; j++) {
        if (dp[j] > length) {
            length = dp[j];
            end = j;
        }
    }

    // Reconstruct
    vector<int> lcis;
    for (int cur = end; cur != -1; cur = parent[cur]) {
        lcis.push_back(B[cur]);
    }
    reverse(lcis.begin(), lcis.end());

    // Output
    cout << length << "\n";
    for (int x : lcis) 
        cout << x << " ";
    cout << "\n";
    return 0;
}

// w