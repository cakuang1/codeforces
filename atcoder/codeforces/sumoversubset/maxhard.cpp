#include<bits/stdc++.h>
using namespace std;
typedef long double ld;
typedef long long ll;
#define rep(a, b) for(ll a = 0; a < (b); ++a)
#define st first
#define nd second
#define pb push_back
#define all(a) a.begin(), a.end()
const int LIM=1e6+7;
ll dpsum[1<<20][20], dpcnt[1<<20], T[LIM];
int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  ll n, q;
  cin >> n >> q;
  ll sto=0, sfrom=0;
  rep(i, n) {
    cin >> T[i];
    sto+=(1ll<<20ll)-T[i];
    sfrom+=T[i];
    ++dpcnt[T[i]];
    ll sum=0;
    rep(j, 20) {
      sum+=T[i]&(1ll<<j);
      dpsum[T[i]][j]+=sum;
    }
  }
  rep(i, 20) rep(j, 1<<20) if(!(j&(1<<i))) dpcnt[j]+=dpcnt[j+(1<<i)];
  rep(i, 20) rep(j, 1<<20) if(!(j&(1<<i))) rep(l, 20) dpsum[j][l]+=dpsum[j+(1<<i)][l];
  while(q--) {
    ll k;
    cin >> k;
    if(k>=sto) {
      k+=sfrom;
      cout << k/n << '\n';
      continue;
    }
    ll ans=0;
    for(ll i=19; i>=0; --i) {
      ll x=(n-dpcnt[ans|(1<<i)])*(1ll<<i);
      x-=dpsum[ans][i]-dpsum[ans|(1<<i)][i];
      if(x<=k) {
        k-=x;
        ans|=1<<i;
      }
    }
    cout << ans << '\n';
  }
}
 



 