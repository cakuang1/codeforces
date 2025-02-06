#include <bits/stdc++.h>
#define fi first
#define se second
#define rep(i,n) for(int i = 0; i < (n); ++i)
#define rrep(i,n) for(int i = 1; i <= (n); ++i)
#define drep(i,n) for(int i = (n)-1; i >= 0; --i)
#define srep(i,s,t) for (int i = s; i < t; ++i)
#define rng(a) a.begin(),a.end()
#define maxs(x,y) (x = max(x,y))
#define mins(x,y) (x = min(x,y))
#define limit(x,l,r) max(l,min(x,r))
#define lims(x,l,r) (x = max(l,min(x,r)))
#define isin(x,l,r) ((l) <= (x) && (x) < (r))
#define pb push_back
#define sz(x) (int)(x).size()
#define pcnt __builtin_popcountll
#define uni(x) x.erase(unique(rng(x)),x.end())
#define snuke srand((unsigned)clock()+(unsigned)time(NULL));
#define show(x) cout<<#x<<" = "<<x<<endl;
#define PQ(T) priority_queue<T,v(T),greater<T> >
#define bn(x) ((1<<x)-1)
#define dup(x,y) (((x)+(y)-1)/(y))
#define newline puts("")
#define v(T) vector<T>
#define vv(T) v(v(T))
using namespace std;
typedef long long int ll;
typedef unsigned uint;
typedef unsigned long long ull;
typedef pair<int,int> P;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll> vl;
typedef vector<P> vp;
inline int in() { int x; scanf("%d",&x); return x;}
template<typename T>inline istream& operator>>(istream&i,v(T)&v)
{rep(j,sz(v))i>>v[j];return i;}
template<typename T>string join(const v(T)&v)
{stringstream s;rep(i,sz(v))s<<' '<<v[i];return s.str().substr(1);}
template<typename T>inline ostream& operator<<(ostream&o,const v(T)&v)
{if(sz(v))o<<join(v);return o;}
template<typename T1,typename T2>inline istream& operator>>(istream&i,pair<T1,T2>&v)
{return i>>v.fi>>v.se;}
template<typename T1,typename T2>inline ostream& operator<<(ostream&o,const pair<T1,T2>&v)
{return o<<v.fi<<","<<v.se;}
template<typename T>inline ll suma(const v(T)& a) { ll res(0); for (auto&& x : a) res += x; return res;}
const double eps = 1e-10;
const ll LINF = 1001002003004005006ll;
const int INF = 1001001001;
#define dame { puts("-1"); return 0;}
#define yn {puts("YES");}else{puts("NO");}
const int MX = 200005;

// Segment tree
struct F { // min func
  typedef ll TT;
  TT d;
  F(TT d=0):d(d) {}
  F& operator+=(const F& f) {
    maxs(d, f.d);
    return *this;
  }
  F operator+(const F& f) const { return F(*this) += f;}
};
struct seg {
  vector<F> d; int n;
  seg(){}
  seg(int mx) {
    n = 1; while (n < mx) n <<= 1;
    d = vector<F>(n<<1);
  }
  void upd(int i) { d[i] = d[i<<1]+d[i<<1|1];}
  F& operator[](int i) { return d[n+i];}
  void init() { for(int i=n-1;i;--i) upd(i);}
  void set(int i, F f) {
    i+=n; d[i] = f;
    for (i>>=1;i;i>>=1) upd(i);
  }
  F get(int l, int r) {
    l += n; r += n;
    F lf, rf;
    while (l < r) {
      if (l&1) lf += d[l++];
      if (r&1) rf = d[--r] + rf;
      l >>= 1; r >>= 1;
    }
    return lf += rf;
  }
};
//


int main() {
  int n;
  scanf("%d",&n);
  vi a(n), b(n);
  cin>>a>>b;
  seg t(n+5);
  ll ans = 0;
  rep(i,n) {
    ll now = t.get(0,a[i]).d + b[i];
    maxs(ans,now);
    t.set(a[i],F(now));
  }
  cout<<ans<<endl;
  return 0;
}




















