#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll k;
    cin >> k;
    string s;
    cin >> s;  
    unordered_map<ll, ll> counter; // Changed to store long long values
    ll n = s.length(); 
    ll sum = 0;
    ll res = 0;
    counter[0] = 1; 
    
    for (ll i = 0; i < n; i++) {
        if (s[i] == '1') {
            sum++;
        }
        res += counter[sum - k]; // Avoid overflow by using long long
        counter[sum]++;
    }
    
    cout << res << endl;
    return 0;
}
