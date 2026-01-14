#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MOD = 1000000007;

int add(int a,int b){ a+=b; if(a>=MOD) a-=MOD; return a; }
int subm(int a,int b){ a-=b; if(a<0) a+=MOD; return a; }
int mul(int a,int b){ return (ll)a*b%MOD; }

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N,Q;
    cin >> N >> Q;
    vector<int>A(N+1);
    for(int i=1;i<=N;i++) 
        cin >> A[i];

    // Precompute prefix sums and prefix sums of squares
    vector<int> S(N+1,0), T(N+1,0);
    for(int i=1;i<=N;i++){
        S[i] = add(S[i-1], A[i]);
        T[i] = add(T[i-1], mul(A[i], A[i]));
    }

    const int INV2 = 500000004;  // modular inverse of 2 mod 1e9+7

    while(Q--){
        int L,R;
        cin >> L >> R;
        int sum   = subm(S[R], S[L-1]);
        int sumsq = subm(T[R], T[L-1]);
        // (sum*sum - sumsq) * INV2 mod
        int ans = subm(mul(sum, sum), sumsq);
        ans = mul(ans, INV2);
        cout << ans << "\n";
    }
    return 0;
}
