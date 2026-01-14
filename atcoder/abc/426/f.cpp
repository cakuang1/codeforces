#include<bits/stdc++.h>
#include<atcoder/all>

using namespace std;
using namespace atcoder;

using ll=long long;
const ll big=4e18;

ll op_pls(ll a,ll b){return a+b;}
ll e_pls(){return 0;}

ll op(ll a,ll b){return min(a,b);}
ll e(){return big;}
ll mapping(ll l,ll r){return l+r;}
ll composition(ll l,ll r){return l+r;}
ll id(){return 0;}

bool g(ll x){ return (x>=0); }

int main(){
  ll n;
  cin >> n;
  vector<ll> a(n);
  for(auto &nx : a){cin >> nx;}
  vector<ll> ini_pls(n,1);
  segtree<ll,op_pls,e_pls> seg_pls(ini_pls);
  lazy_segtree<ll, op, e, ll, mapping, composition, id> seg(a);

  ll q;
  cin >> q;
  while(q--){
    ll l,r,k;
    cin >> l >> r >> k;
    l--;
    ll res=seg_pls.prod(l,r)*k;
    seg.apply(l,r,-k);
    while(seg.prod(l,r)<0){
      ll pos=seg.max_right<g>(l);
      res+=seg.get(pos);
      seg.set(pos,big);
      seg_pls.set(pos,0);
    }
    cout << res << "\n";
  }
  return 0;
}

//  werpoapo nd sinstiosnse stis wha t
// werwh osdgousetsv sres pso pwrand siunsier t
/ 