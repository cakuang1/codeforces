#include <bits/stdc++.h>
using namespace std;

using ll = long long;








int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    ll n, x,y; cin >> n >> x >> y; 

    // solve both cases indepenetendetn werly
    
    vector<ll> first;
    vector<ll> second;

    for (int i = 0 ; i < n; i ++) {
        ll curr; cin >> curr; 
        if (i % 2) {
            second.push_back(curr); 
        } else{
            first.push_back(curr); 
        }
    }
    unordered_map<ll,ll> m11;
    unordered_map<ll,ll> m12;
    int half = first.length()/2;
    for (int i = 0 ; i < half ; i ++) {
        
    }

    for (int i = half ; i < first.length() ; i ++) {
        
     }
    

    return 0;

    // split wethte problem into two halves 
}


