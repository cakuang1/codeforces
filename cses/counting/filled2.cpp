#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<string> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
        // convert 'A'.. into 0..k-1
        for(char &c : a[i]) c = c - 'A';
    }

    // answer for each letter 0..k-1
    vector<ll> ans(k, 0);

    // up[i][j] = number of identical chars up from (i,j)
    vector<vector<int>> up(n, vector<int>(n, 0));

    // process row by row
    for(int i = 0; i < n; i++){
        // stack of (height, width)
        vector<pair<int,int>> stk;
        ll tar = 0;        // running total for this horizontal block
        for(int j = 0; j < n; j++){
            // compute up[i][j]
            if(i > 0 && a[i][j] == a[i-1][j])
                up[i][j] = up[i-1][j] + 1;
            else
                up[i][j] = 1;

            // if letter changes from left, reset block
            if(j > 0 && a[i][j] != a[i][j-1]){
                stk.clear();
                tar = 0;
            }

            // histogram stack: count all rectangles ending at (i,j)
            int len = 1;
            while(!stk.empty() && stk.back().first >= up[i][j]){
                tar -= (ll)stk.back().first * stk.back().second;
                len += stk.back().second;
                stk.pop_back();
            }
            stk.emplace_back(up[i][j], len);
            tar += (ll)up[i][j] * len;

            // add all rectangles whose bottom‑right corner is (i,j)
            ans[ a[i][j] ] += tar;
        }
    }
    for(int c = 0; c < k; c++){
        cout << ans[c] << "\n";
    }
    return 0;
}
