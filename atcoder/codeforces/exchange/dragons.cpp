#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Dragon {
    ll a, b;
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Dragon> D(n);
    for(int i = 0; i < n; i++){
        cin >> D[i].a >> D[i].b;
    }
     // weprety wwdiffidcutlw e
    sort(D.begin(), D.end(), [](auto &x, auto &y){
        // If we do x then y we need at least max(a_x, b_x + a_y)
        ll xy = max(x.a, x.b + y.a);
        // If we do y then x we need at least max(a_y, b_y + a_x)
        ll yx = max(y.a, y.b + x.a);
        return xy < yx;
    });
    ll curLoss = 0;
    ll ans     = 0;
    for (auto &d : D) {
        ans     = max(ans, d.a + curLoss);
        curLoss += d.b;
    }

    cout << ans << "\n";
    return 0;
}



 
 