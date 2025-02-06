#include <iostream>
#include <sstream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <string>
#include <cstring>
#include <cassert>
#include <iomanip>
#include <algorithm>
#include <set>
#include <map>
#include <ctime>
#include <cmath>

#define forn(i, n) for(int i=0;i<n;++i)
#define fore(i, l, r) for(int i = int(l); i <= int(r); ++i)
#define sz(v) int(v.size())
#define all(v) v.begin(), v.end()
#define pb push_back
#define mp make_pair
#define x first
#define y1 ________y1
#define y second
#define ft first
#define sc second
#define pt pair<int, int>

template<typename X> inline X abs(const X& a) { return a < 0? -a: a; }
template<typename X> inline X sqr(const X& a) { return a * a; }

typedef long long li;
typedef long double ld;

using namespace std;

const int INF = 1000 * 1000 * 1000;
const ld EPS = 1e-9;
const ld PI = acos(-1.0);

const int N = 200 * 1000 + 13;

int n;
int a[N];

inline void read() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }   
}

inline void solve() {   
    int ans = INF;
    for (int i = 0; i < n - 1; i++) {
        int cur = 0;
        int x = a[i], y = a[i + 1];
        if (x < y) {
            swap(x, y);
        }
        int cnt = min(x - y, (x + 1) / 2);
        cur += cnt;
        x -= 2 * cnt;
        y -= cnt;
        if (x > 0 && y > 0) {
            cur += (x + y + 2) / 3;
        }
        ans = min(ans, cur);    
    }

    for (int i = 0; i < n - 2; i++) {
        int cur = 0;
        int x = a[i], y = a[i + 2];
        if (x < y) {
            swap(x, y);
        }
        int cnt = (x - y + 1) / 2;
        cur += cnt;
        cur += y;
        ans = min(ans, cur);
    }
    
    sort(a, a + n);
    ans = min(ans, (a[0] + 1) / 2 + (a[1] + 1) / 2);
    cout << ans << endl;
}

int main () {
#ifdef fcspartakm
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
#endif
    srand(time(NULL));
    cerr << setprecision(10) << fixed;
       
    read();
    solve();
 
    //cerr << "TIME: " << clock() << endl;
}