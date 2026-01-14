#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
#define rep(a, b) for(int a = 0; a < (b); ++a)
#define st first
#define nd second
#define pb push_back
#define all(a) a.begin(), a.end()
const int LIM=1e5+7;
ll T[LIM], P[LIM], n, k;
void solve() {
  rep(i, n) T[i]=P[i];
  ll ans=0;
  for(ll i=60; i>=0; --i) {
    ll sum=0;
    rep(j, n) {
      if(T[j]&(1ll<<i)) continue;
      ll p=(T[j]/(1ll<<i))*(1ll<<i)+(1ll<<i);
      p+=ans^(p&ans);
      sum+=p-T[j];
      if(sum > k){
          break;
      }
    }

    if(sum>k) continue;
    rep(j, n) {
      if(T[j]&(1ll<<i)) continue;
      ll p=(T[j]/(1ll<<i))*(1ll<<i)+(1ll<<i);
      p+=ans^(p&ans);
      T[j]=p;
    }
    ans+=1ll<<i;
    k-=sum;
  }
  cout << ans << '\n';
}
int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int q;
  cin >> n >> q;
  rep(i, n) cin >> P[i];
  while(q--) {
    cin >> k;
    solve();
  }
} 