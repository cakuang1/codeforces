#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    // We'll allow mex up to n*n, which is safe for n<=100
    int MAXV = n*n + 1;

    // rowUsed[i][k] = have we used value k to the left in row i?
    // colUsed[j][k] = have we used value k above in column j?
    vector<vector<bool>> rowUsed(n, vector<bool>(MAXV,false));
    vector<vector<bool>> colUsed(n, vector<bool>(MAXV,false));

    vector<vector<int>> ans(n, vector<int>(n,0));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            // find mex
            int k = 0;
            while(k < MAXV && (rowUsed[i][k] || colUsed[j][k])) 
                ++k;
            ans[i][j] = k;
            // mark it used
            rowUsed[i][k] = true;
            colUsed[j][k] = true;
        }
    }
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << ans[i][j] << (j+1<n ? ' ' : '\n');
        }
    }
    
    return 0;
}
