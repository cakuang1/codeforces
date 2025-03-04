// #pragma GCC optimize("Ofast,unroll-loops")
// #pragma GCC target("avx,avx2,fma")

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ull unsigned long long
#define dd double
#define ld long double
#define sl(n) scanf("%lld", &n)
#define si(n) scanf("%d", &n)
#define sd(n) scanf("%lf", &n)
#define pll pair <ll, ll>
#define pii pair <int, int>
#define mp make_pair
#define pb push_back
#define all(v) v.begin(), v.end()
#define inf (1LL << 61)
#define loop(i, start, stop, inc) for(ll i = start; i <= stop; i += inc)
#define for1(i, stop) for(ll i = 1; i <= stop; ++i)
#define for0(i, stop) for(ll i = 0; i < stop; ++i)
#define rep1(i, start) for(ll i = start; i >= 1; --i)
#define rep0(i, start) for(ll i = (start-1); i >= 0; --i)
#define ms(n, i) memset(n, i, sizeof(n))
#define casep(n) printf("Case %lld:", ++n)
#define pn printf("\n")
#define pf printf
#define EL '\n'
#define fastio std::ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

// === DEBUG MACRO STARTS HERE === //
#ifndef ONLINE_JUDGE
#define DEBUG
#define SYS_COL system("COLOR")
#endif

int recur_depth = 0;
#ifdef DEBUG
#define dbg(x) {++recur_depth; auto x_=x; --recur_depth; SYS_COL; \
                cerr<<string(recur_depth, '\t')<<"\e[91m"<<__func__<<":" \
                <<__LINE__<<"\t"<<#x<<" = "<<x_<<"\e[39m"<<endl;}

template<typename Ostream, typename Cont>
typename enable_if<is_same<Ostream,ostream>::value,
            Ostream&>::type operator<<(Ostream& os,  const Cont& v) {
	os<<"[";
	for(auto& x:v){os<<x<<", ";}
	return os<<"]";
}
template<typename Ostream, typename  ...Ts>
Ostream& operator<<(Ostream& os,  const pair<Ts...>& p){
	return os<<"{"<<p.first<<", "<<p.second<<"}";
}
#else
#define dbg(x)
#endif
// === DEBUG MACRO ENDS HERE === //

#define ff first
#define ss second

const ll sz = 1e5 + 10;
vector <ll> g[sz], g2[sz], comp;
bitset <sz> ase;
ll tot, vis[sz], cyc = 0;

void dfs(ll u)
{
    vis[u] = 1;

    for(ll &v : g[u]) {
        if(!vis[v])
            dfs(v);
        else if(vis[v] == 1)
            cyc = 1;
    }

    vis[u] = 2;
}

void dfs2(ll u)
{
    vis[u] = 1;
    comp.pb(u);

    for(ll &v : g2[u])
        if(!vis[v])
            dfs2(v);
}

int main()
{
    ll n, m;
    sl(n), sl(m);

    for1(i, m) {
        ll u, v;
        sl(u), sl(v);

        g[u].pb(v);

        g2[u].pb(v), g2[v].pb(u);

        ase[u] = ase[v] = 1;
    }

    ll ans = 0;

    for1(i, n) {
        if(!ase[i] || vis[i]) continue;

        comp.clear();
        dfs2(i);

        for(ll &x : comp) vis[x] = 0;

        cyc = 0;
        for(ll &x : comp) {
            if(vis[x])
                continue;

            dfs(x);
        }

        if(cyc) ans += comp.size();
        else ans += comp.size() - 1;
    }

    cout << ans << EL;

    return 0;
}

