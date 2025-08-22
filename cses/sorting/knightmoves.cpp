#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll knightDist(ll x, ll y) {
    ll dx = abs(x - 1), dy = abs(y - 1);
    ll a = min(dx, dy), b = max(dx, dy);
    if (a==0 && b==0) return 0;
    if (a==1 && b==0) return 3;
    if (a==2 && b==2) return 4;
    // base estimate
    ll d = max( (b+1)/2, (a + b + 2)/3 );
    // adjust parity: knight moves alternate square colors each move,
    // so d must have same parity as (a+b)
    if ((d % 2) != ((a + b) % 2)) d++;
    return d;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    while(n--){
        ll x,y;
        cin >> x >> y;
        cout << knightDist(x,y) << "\n";
    }
    return 0;
}

// kngiw