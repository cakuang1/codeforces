#include <bits/stdc++.h>
using namespace std;

int dp[1001][1001];
char op[1001][1001];  // 'M'atch, 'R'eplace, 'D'elete, 'I'nsert

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s, t;
    cin >> s >> t;
    int n = s.size(), m = t.size();

    // 1) Base cases
    for(int i = n; i >= 0; --i){
        for(int j = m; j >= 0; --j){
            if(i == n){
                dp[i][j] = m - j;
                op[i][j] = 'I';  // we'll do m-j inserts
            }
            else if(j == m){
                dp[i][j] = n - i;
                op[i][j] = 'D';  // we'll do n-i deletes
            }
            else {
                // 2) match or replace
                int best = INT_MAX;
                if(s[i] == t[j]){
                    best = dp[i+1][j+1];
                    op[i][j] = 'M';
                } else {
                    best = 1 + dp[i+1][j+1];
                    op[i][j] = 'R';
                }
                // 3) delete s[i]
                if(1 + dp[i+1][j] < best){
                    best = 1 + dp[i+1][j];
                    op[i][j] = 'D';
                }
                // 4) insert t[j]
                if(1 + dp[i][j+1] < best){
                    best = 1 + dp[i][j+1];
                    op[i][j] = 'I';
                }
                dp[i][j] = best;
            }
        }
    }

    // 5) Print distance
    cout << dp[0][0] << "\n";

    // 6) Backtrack and emit operations
    int i = 0, j = 0;
    int pos = 1;  // position in the **current** string
    while(i < n || j < m){
        char c = op[i][j];
        if(c == 'M'){
            // match, no output
            i++; j++; pos++;
        }
        else if(c == 'R'){
            // replace s[i] -> t[j]
            cout << "REPLACE " << pos << " " << t[j] << "\n";
            i++; j++; pos++;
        }
        else if(c == 'D'){ 
            // delete s[i]
            cout << "DELETE " << pos << "\n";
            i++; 
            // pos stays the same, since the next character slides into this position
        }
        else if(c == 'I'){
            // insert t[j] at pos
            cout << "INSERT " << pos << " " << t[j] << "\n";
            j++;
            pos++; 
        }
    }
    

    return 0;
}
