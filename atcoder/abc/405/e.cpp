#include <bits/stdc++.h>
using namespace std;
using ll = long long;

static const ll MOD = 998244353;

// fast exponentiation
ll modexp(ll b, ll e=MOD-2){
    ll r = 1;
    while(e){
        if(e&1) r = (r*b) % MOD;
        b = (b*b) % MOD;
        e >>= 1;
    }
    return r;
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll A,B,C,D;
    cin >> A >> B >> C >> D;
    ll N = A+B+C+D + 5;  // enough for all choose calls

    // build factorials [0..N)
    vector<ll> fac(N), ifac(N);
    fac[0] = 1;
    for(int i = 1; i < N; i++) fac[i] = fac[i-1]*i % MOD;
    ifac[N-1] = modexp(fac[N-1]);
    for(int i = N-1; i > 0; i--) ifac[i-1] = ifac[i]*i % MOD;

    auto choose = [&](ll n, ll k)->ll{
        if(k<0||k>n) return 0;
        return fac[n] * ifac[k] % MOD * ifac[n-k] % MOD;
    };

    ll ans = 0;
    // sum_{i=0..C} C(A+B+i, B) * C((C-i)+(D-1), D-1)
    for(ll i = 0; i <= C; i++){
        ll left  = choose(A + B + i, B);
        ll right = choose((C - i) + (D - 1), D - 1);
        ans = (ans + left * right) % MOD;
    }

    cout << ans << "\n";
    return 0;
}
