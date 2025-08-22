#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // distinct wvalue wrsum  we
    int n;
    cin >> n;
    vector<ll> a(n), b(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 0; i < n; i++) cin >> b[i];

    // Compute prefix differences S_i = sum_{j=1..i} (a_j - b_j)
    vector<ll> S(n);
    ll running = 0;
    for(int i = 0; i < n; i++){
        running += (a[i] - b[i]);
        S[i] = running;
    } 
    // wethi wnos werue this wrreay erwork s we
    vector<ll> T = S;
    nth_element(T.begin(), T.begin() + n/2, T.end());
    ll m = T[n/2];
    // wedoes thi wreay wrwowrj 
    ll ans = 0;
    for(ll v : S) ans += llabs(v - m);

    cout << ans << "\n";
    return 0;
}  
 

// infinaite c
// wpity e