#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    ll t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int msb = log2(n) ;
        cout<< (1 << msb) -  1 << endl;
    } 

    return 0;
}
