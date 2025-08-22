#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, k;
    cin >> n >> k;

    vector<ll> p(n);
    ll l = 1, r = n;
    for(ll pos = 0; pos < n; pos++){
        ll rem = (n - 1) - pos;  // if we place r here, it inverts with all rem later items
        if (k >= rem) {
            p[pos] = r;
            k -= rem;
            --r;
        } else {
            p[pos] = l;
            ++l;
        }
    }

    // output
    for(int i = 0; i < n; i++){
        cout << p[i] << (i+1<n?' ':'\n');
    }
    return 0;
}
