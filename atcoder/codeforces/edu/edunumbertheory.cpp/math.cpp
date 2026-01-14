#include <bits/stdc++.h>
#define ll long long
#define pb push_back
using namespace std;

int isPowerOfTwo(ll x) {
    if(x && (!(x&(x-1)))) return 0;
    return 1;
} 

vector<int> pr;
void SieveOfEratosthenes(int n){
    vector<bool> prime(n+1,true);
    for (ll p=2; p*p <= n; p++) if (prime[p] == true) for (ll i=p*2; i<=n; i += p) prime[i] = false;
    for (int p=2; p<=n; p++) if (prime[p]) pr.pb(p);
}

int main() {

    int n;
    cin >> n;
    
    SieveOfEratosthenes(n);
    
    ll ans = 1;
    
    map<ll,ll> m;
    
    for(int i = 0 ; i < pr.size() && n; ++i) {
        if(n % pr[i] == 0){
            m[pr[i]]++;
            n /= pr[i];
            i--;
        }
    }
   
    ll steps = 0;
    for(auto it = m.begin(); it!=m.end(); ++it){
        ans *= it->ff;
        steps = max(steps, it->ss);
    }
    bool flag = 0;
    for(auto it = m.begin(); it!=m.end(); ++it){
        if(it->ss != steps){
            flag = 1;
            break;
        }
    }

    int temp = 0;
    if(flag) temp = 1;
    else temp = isPowerOfTwo(steps);
    if(steps == 1) steps--;
    else if(steps != 0) steps = ceil(log2(steps)) + temp;
    cout << ans << " " << steps << endl;
} 

// w