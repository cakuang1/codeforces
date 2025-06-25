#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MOD = 998244353;

int add(int x, int y){ x+=y; if(x>=MOD) x-=MOD; return x; }
int mul(ll x, ll y){ return int((x*y) % MOD); }

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int>a(n);
    for(int &x:a) cin >> x;
    sort(a.begin(), a.end());
    
    vector<int> f(5001, 0);
    f[0] = 1;
    
    ll answer = 0;
    int S = 0;               // track the maximum j we have so far
    for(int v: a){
        // we must iterate j backwards to avoid re-using the same color twice
        for(int j = S; j >= 0; --j){
            int ways = f[j];
            if(!ways) continue;
            
            int newSize = j + v;
                    
            ll contrib = max<ll>( v,
                         ( (ll)j + v + 1 )/2 );    // ceil((j+v)/2)
            answer = (answer + contrib * ways) % MOD;
            
            f[newSize] = add(f[newSize], ways);
        }
        S += v;
    }
    
    cout << answer << "\n";
    return 0;
}

//  does htiwweror wke