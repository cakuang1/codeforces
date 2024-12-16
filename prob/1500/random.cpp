#include <bits/stdc++.h>

#pragma optimization_level 3
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math,O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx")
#pragma GCC optimize("Ofast")//Comment optimisations for interactive problems (use endl)
#pragma GCC target("avx,avx2,fma")
#pragma GCC optimization ("unroll-loops")

using namespace std;

struct PairHash {inline std::size_t operator()(const std::pair<int, int> &v) const { return v.first * 31 + v.second; }};

// speed
#define Code ios_base::sync_with_stdio(false);
#define By ios::sync_with_stdio(0);
#define Sumfi cout.tie(NULL);

// alias
using ll = long long;
using ld = long double;
using ull = unsigned long long;

// constants
const ld PI = 3.14159265358979323846;  /* pi */
const ll INF = 1e18;
const ld EPS = 1e-9;
const ll MAX_N = 1e9 + 1;
const ll mod = 1e9 + 7;

// typedef
typedef pair<ll, ll> pll;
typedef vector<pll> vpll;
typedef array<ll,3> all3;
typedef array<ll,5> all5;
typedef vector<all3> vall3;
typedef vector<all5> vall5;
typedef vector<ld> vld;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<int> vi;
typedef pair<string, string> pss;
typedef vector<pss> vpss;
typedef vector<string> vs;
typedef vector<vs> vvs;
typedef unordered_set<ll> usll;
typedef unordered_set<pll, PairHash> uspll;
typedef unordered_map<ll, ll> umll;
typedef unordered_map<pll, ll, PairHash> umpll;

// macros
#define rep(i,m,n) for(ll i=m;i<n;i++)
#define rrep(i,m,n) for(ll i=n;i>=m;i--)
#define all(a) begin(a), end(a)
#define rall(a) rbegin(a), rend(a)
#define ZERO(a) memset(a,0,sizeof(a))
#define MINUS(a) memset(a,0xff,sizeof(a))
#define ASCEND(a) iota(all(a),0)
#define sz(x) ll((x).size())
#define pyes cout<<"YES\n";
#define pno cout<<"NO\n";
#define pneg1 cout<<"-1\n";
#define ppossible cout<<"POSSIBLE\n";
#define pimpossible cout<<"IMPOSSIBLE\n";
#define CASE(x) cout<<"Case #"<<x<<": ";

// utility functions
template <typename T>
void print(T &&t)  { cout << t << "\n"; }
template<typename T>
void printv(vector<T>v){ll n=v.size();rep(i,0,n)cout<<v[i]<<" ";cout<<"\n";}
void fileIO() {freopen("input.txt","r",stdin); freopen("output.txt","w",stdout);}
//void readf() {freopen("", "rt", stdin);}


ll __gcd(ll x, ll y) { return !y ? x : __gcd(y, x % y); }
ll __lcm(ll x, ll y) { return x / __gcd(x,y) * y; }
ll modpow(ll n, ll x, ll MOD = mod) { if(!x) return 1; ll res = modpow(n,x>>1,MOD); res = (res * res) % MOD; if(x&1) res = (res * n) % MOD; return res; }

ld solve(vll A, vector<pair<ll,ld>> B) {
    vll S = A;
    sort(all(S));
    ll limit = sz(A);
    rrep(i,0,sz(A) - 1) {
        if(A[i] == S[i]) limit = i;
        else break;
    }
    if(limit == 0) return 1.;
    ld res = 1.0;
    rep(i,0,sz(B)) {
        auto [r, p] = B[i];
        if(r >= limit) res *= (1. - p);
    }
    return 1. - res;
}

int main() {
    Code By Sumfi

    cout.precision(12);

    ll tc = 1;
    cin>>tc;
    rep(i,1,tc+1) {
        ll n,m;
        cin>>n>>m;
        vll A(n);
        vector<pair<ll,ld>> B(m);
        rep(i,0,n) cin>>A[i];
        rep(i,0,m) cin>>B[i].first>>B[i].second;
        print(solve(A,B));
    }

    return 0;
}