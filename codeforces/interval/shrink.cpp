#include<bits/stdc++.h>

using namespace std;

#define fore(i, l, r) for(int i = int(l); i < int(r); i++)
#define sz(a) int((a).size())

#define x first
#define y second

typedef long long li;
typedef long double ld;
typedef pair<int, int> pt;

template<class A, class B> ostream& operator <<(ostream& out, const pair<A, B> &p) {
    return out << "(" << p.x << ", " << p.y << ")";
}
template<class A> ostream& operator <<(ostream& out, const vector<A> &v) {
    out << "[";
    fore(i, 0, sz(v)) {
        if(i) out << ", ";
        out << v[i];
    }
    return out << "]";
}

const int INF = int(1e9);
const li INF64 = li(1e18);
const ld EPS = 1e-9;

const int N = 555;
int n, a[N];

inline bool read() {
    if(!(cin >> n))
        return false;
    fore(i, 0, n)
        cin >> a[i];
    return true;
}

int dp[N][N];

int calcDP(int l, int r) {
    assert(l < r);
    if(l + 1 == r)
        return dp[l][r] = a[l];
    if(dp[l][r] != 0)
        return dp[l][r];
    
    dp[l][r] = -1;
    fore(mid, l + 1, r) {
        int lf = calcDP(l, mid);
        int rg = calcDP(mid, r);
        if(lf > 0 && lf == rg)
            return dp[l][r] = lf + 1;
    }
    return dp[l][r];
}

int dp2[N];

inline void solve() {
    fore(i, 0, N)
        dp2[i] = INF;
    
    dp2[0] = 0;
    fore(i, 0, n) {
        fore(j, i + 1, n + 1) {
            if(calcDP(i, j) > 0)
                dp2[j] = min(dp2[j], dp2[i] + 1);
        }
    }
    cout << dp2[n] << endl;
}

int main() {
#ifdef _DEBUG
    freopen("input.txt", "r", stdin);
    int tt = clock();
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cout << fixed << setprecision(15);
    
    if(read()) {
        solve();
        
#ifdef _DEBUG
        cerr << "TIME = " << clock() - tt << endl;
        tt = clock();
#endif
    }
    return 0;
}



