#include<bits/stdc++.h>

using namespace std;

const int MOD = 998244353;
const int N = 5005;

void upd(int &a, int b){
    a += b;
    a %= MOD;
}

int mul(int a, int b){
    return (a * 1LL * b) % MOD;
}

int bp(int a, int n){
    int res = 1;
    for(; n > 0; n >>= 1){
        if(n & 1) res = mul(res, a);
        a = mul(a, a);
    }
    return res;
}

int getInv(int a){
    int ia = bp(a, MOD - 2);
    assert(mul(a, ia) == 1);
    return ia;
}

int n;
int cnt[N];
int suf[N];
int dp[N][N];
int sum[N][N];
int inv[N];

int main(){
    for(int i = 1; i < N; ++i)
        inv[i] = getInv(i);
        
    cin >> n;
    for(int i = 0; i < n; ++i){
        int x;
        cin >> x;
        ++cnt[x];
    }
    cnt[0] = 1;
    for(int i = N - 2; i >= 0; --i)
        suf[i] = suf[i + 1] + cnt[i];
        
    for(int x = n; x >= 0; --x)
        for(int y = n; y >= 0; --y){
            if(cnt[x] == 0){
                upd(sum[x][y], sum[x + 1][y]);
                continue;
            }
            int s = n - y;
            if(s <= 0){
                upd(sum[x][y], sum[x + 1][y]);
                continue;
            }
            
            upd(dp[x][y], mul(cnt[x] - 1, inv[s]));
            upd(dp[x][y], mul(sum[x + 1][y + 1], inv[s]));
            
            upd(sum[x][y], sum[x + 1][y]);
            upd(sum[x][y], mul(cnt[x], dp[x][y]));
        }
    
    cout << dp[0][0] << endl;
	return 0;
}