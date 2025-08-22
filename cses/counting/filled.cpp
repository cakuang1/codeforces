#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<string> grid(n);
    for(int i = 0; i < n; i++){
        cin >> grid[i];
    }

    // Use two rolling arrays of length n
    vector<int> dp_prev(n, 0), dp_cur(n, 0);

    // For each letter L = 'A', 'B', ..., 'A'+k-1
    for(int ci = 0; ci < k; ci++){
        char L = char('A' + ci);
        ll count = 0;

        // reset dp_prev for this letter
        fill(dp_prev.begin(), dp_prev.end(), 0);

        // row by row DP
        for(int i = 0; i < n; i++){
            int left = 0;  // dp_cur[j-1]
            for(int j = 0; j < n; j++){
                if(grid[i][j] == L){
                    int above    = dp_prev[j];
                    int diagLeft = (j > 0 ? dp_prev[j-1] : 0);
                    dp_cur[j] = 1 + min( above, min(left, diagLeft) );
                } else {
                    dp_cur[j] = 0;
                }
                count += dp_cur[j];
                left = dp_cur[j];
            }
            // move current row into previous for next iteration
            dp_prev.swap(dp_cur);
        }

        cout << count << "\n";
    }

    return 0;
}
