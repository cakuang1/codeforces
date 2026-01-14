#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<ll> a(n), b(n), c(m);
    ll A = 0;
    for(int i = 0; i < n; i++){
        cin >> a[i];
        A = max(A, a[i]);        // track max a_i
    }
    for(int i = 0; i < n; i++){
        cin >> b[i];
    }
    for(int j = 0; j < m; j++){
        cin >> c[j];
    }

    // 1) Build best[x] = min(a_i - b_i) over all i with a_i <= x
    const ll INF = (ll)1e18;
    vector<ll> best(A+1, INF);
    for(int i = 0; i < n; i++){
        ll delta = a[i] - b[i];
        best[a[i]] = min(best[a[i]], delta);
    }
    // prefix‐min so that best[x] = min over all a_i <= x
    for(int x = 1; x <= A; x++){
        best[x] = min(best[x], best[x-1]);
    }

    // 2) Precompute ans[x] for x = 0..A by dp
    //    ans[0] = 0;  ans[x] = 2 + ans[x - best[x]]
    vector<ll> ans(A+1, 0);
    for(int x = 1; x <= A; x++){
        // if best[x] is INF, you cannot do even one cycle; but problem guarantees a_i>=1
        ans[x] = 2 + ans[x - best[x]];
    }

    // 3) For each pile c[j], if c[j] <= A just add ans[c[j]].
    //    Otherwise, first do k full cycles of size best[A]:
    //      k = ceil((c[j]-A) / best[A])
    //    then rem = c[j] - k*best[A] ≤ A, so add ans[rem].
    ll res = 0;
    ll dA = best[A];
    for(ll x : c){
        if(x <= A){
            res += ans[x];
        } else {
            // how many cycles to bring x down to ≤ A:
            ll need = x - A;
            ll k = (need + dA - 1) / dA;
            ll rem = x - k * dA;  // now rem ≤ A
            res += 2*k + ans[rem];
        }
    }

    cout << res << "\n";
    return 0;
}
