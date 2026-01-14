#include <bits/stdc++.h>

#define int long long
#define pb emplace_back
#define mp make_pair
#define x first
#define y second
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()

typedef long double ld;
typedef long long ll;

using namespace std;

mt19937 rnd(time(nullptr));

const int inf = 1e9;
const int M = 1e9 + 7;
const ld pi = atan2(0, -1);
const ld eps = 1e-6;

struct min_max{
    int mx1, mx2, mn1, mn2;

    void fix_mx(){
        if(mx1 < mx2){
            swap(mx1, mx2);
        }
    }
    void fix_mn(){
        if(mn1 > mn2){
            swap(mn1, mn2);
        }
    }

    min_max(int a, int b){
        mx1 = mn1 = a;
        mx2 = mn2 = b;
        fix_mx();
        fix_mn();
    }

    void add(int x){
        mx2 = max(mx2, x);
        mn2 = min(mn2, x);
        fix_mx();
        fix_mn();
    }

    int get_seg(int x){
        pair<int, int> res = {mn1, mx1};
        if(x == mn1) res.x = mn2;
        if(x == mx1) res.y = mx2;
        return res.y - res.x + 1;
    }
};

void solve(int tc){
    int n;
    cin >> n;
    vector<pair<int, int>> coord(n);
    for(auto &e: coord){
        cin >> e.x >> e.y;
    }
    if(n <= 2){
        cout << n;
        return;
    }

    min_max xc(coord[0].x, coord[1].x), yc(coord[0].y, coord[1].y);
    for(int i = 2; i < n; ++i){
        xc.add(coord[i].x);
        yc.add(coord[i].y);
    }

    int ans = xc.get_seg(-1) * yc.get_seg(-1);
    for(int i = 0; i < n; ++i){
        int x = xc.get_seg(coord[i].x);
        int y = yc.get_seg(coord[i].y);
        if(x * y == n - 1){
            ans = min(ans, min((x + 1) * y, x * (y + 1)));
        }
        else{
            ans = min(ans, x * y);
        }
    }
    cout << ans;
}


bool multi = true;

signed main() {
    int t = 1;
    if (multi)cin >> t;
    for (int i = 1; i <= t; ++i) {
        solve(i);
        cout << "\n";
    }
    return 0;
}