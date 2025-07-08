#include<iostream>
#include<algorithm>
#include <cstring>

using namespace std;
int a[710];
bool g[710][710];
int dp[710][710][2];
int dfs(int l, int r, int k){
    if(l > r) return 1;
    if(dp[l][r][k] != -1) return dp[l][r][k];
    int x = k?r+1:l-1;
    for(int i = l;i <= r;i ++){
        if(!g[x][i]) continue;
        if(dfs(l, i - 1, 1) && dfs(i + 1, r, 0)) return dp[l][r][k] = 1;
    }
    return dp[l][r][k] = 0;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    memset(dp, -1, sizeof(dp));
    int n;
    cin >> n;
    for(int i = 1;i <= n;i ++) cin >> a[i];
    // 预处理存下互质的对（这里不存也是可以过的，n<=700）
    for(int i = 1;i <= n;i ++)
        for (int j = 1; j < i; j++){
            if (__gcd(a[i], a[j]) > 1){
                g[i][j] = true;
                g[j][i] = true;
            }
        }
    for(int i = 1;i <= n;i ++){
    //继续递归子区间，找符合条件的根
        if(dfs(1, i - 1, 1) && dfs(i + 1, n, 0)){
            cout << "Yes";
            return 0;
        }
    }

    cout << "No";
    return 0;
}

