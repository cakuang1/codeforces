#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n; 
    // Create a vector of size n+1 and assign a0 = 0.
    vector<int> a(n+1, 0);
    a[0] = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i]; 
    }
    
    ll res = 0;
    // Process adjacent pairs: (a[i-1], a[i]) for i = 1 to n.
    for (int i = 1; i <= n; i++) { 
        int prev = a[i - 1]; 
        int cur = a[i]; 
        if (prev == cur) continue; 
        if (cur > prev) {
            // When a_i > a_{i-1}: l can range from (a_{i-1}+1) to a_i
            // and r can range from a_i to n.
            ll first = cur - prev;             // number of choices for l
            ll second = (ll)n - cur + 1;         // number of choices for r
            res = (res + first * second);
        } else { // cur < prev
            // When a_i < a_{i-1}: l can range from 1 to a_i,
            // and r can range from a_i to (a_{i-1}-1).
            ll first = cur;                    // choices for l
            ll second = prev - cur;            // choices for r
            res = (res + first * second) ;
        }
    }
    
    cout << res << "\n";
    return 0;
}
