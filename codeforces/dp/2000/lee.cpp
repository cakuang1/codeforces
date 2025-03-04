
#include <bits/stdc++.h>

#define IOS ios::sync_with_stdio(0), cin.tie(), cout.tie();

using namespace std;

typedef long long ll;

const int maxBt = 30;
const int mod = 1e9+7;

int cnt[maxBt];

int slv(){
    int n;
    cin >> n;

    int a[n];
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }

    int to[n+1]; //powers of 2

    to[0] = 1;
    for(int i = 1; i <= n; i++){
        to[i] = to[i-1]*2 % mod;
    }

    for(int i = 0; i < n; i++){
        int x = 0;
        for(int k = 0; k < maxBt; k++){
            if(a[i] & 1)break;
            a[i] >>= 1;
            x++;
        }
        cnt[x]++;
    }

    int ans = to[n] - to[n-cnt[0]] + mod;
    if(ans >= mod)ans -= mod;

    int y = n-cnt[0];

    for(int l = 1; l < maxBt; l++){
        int x = y;
        y -= cnt[l];
        if(x-y < 2)continue;
        int delta = to[x-1]-to[y]+mod;
        if(delta >= mod)delta -= mod;
        ans += delta;
        if(ans >= mod)ans -= mod;
    }

    return ans;
}


signed main(){
    IOS

    cout << slv() << '\n';

}

