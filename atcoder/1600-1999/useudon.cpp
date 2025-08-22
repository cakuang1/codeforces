#include<bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i,a,b) for(int i=(int)(a);i<(int)(b);i++)
#include <atcoder/modint>
using mint = atcoder::modint998244353;

mint solve_sub(ll R, vector<int> A, vector<int> B){
    int N = A.size();
    vector<ll> sumA(N + 1), sumB(N + 1);
    rep(i, 0, N){
        sumA[i + 1] = sumA[i] + A[i];
        sumB[i + 1] = sumB[i] + B[i];
    }
    vector<mint> dp(N + 1);
    dp[0] = 1;
    rep(i, 0, N + 1){
        rep(j, i, N) dp[j + 1] += dp[j];
        rep(j, i, N + 1) if (sumA[j] - sumB[i] - sumA[N] + sumB[N] > R){
            dp[j] = 0;
        }
    }
    return dp[N];
}

int main(){
    ll N, L, R;
    cin >> N >> L >> R;
    vector<int> A(N), B(N);
    rep(i, 0, N) cin >> A[i];
    rep(j, 0, N) cin >> B[j];
    cout << (solve_sub(R, A, B) - solve_sub(L - 1, A, B)).val() << "\n";
}

 

