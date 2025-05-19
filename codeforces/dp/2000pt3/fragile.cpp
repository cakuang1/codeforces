#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

ll even(ll x) {
    // Largest even number <= x.
    if(x < 2) return 0;
    return (x % 2 == 0 ? x : x - 1);
}

ll odd(ll x) {
    // Largest odd number <= x.
    // For x>=1: if x is odd, return x; if even, return x-1.
    if(x < 1) return 0;
    return (x % 2 == 1 ? x : x - 1);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    // There are n-1 bridges. a[i] is the capacity for the bridge between platform i and i+1.
    vector<ll> a(n, 0); // We'll store a[1]...a[n-1] in a[1..n-1] (and a[0] is unused).
    for (int i = 1; i <= n-1; i++){
        cin >> a[i];
    }
    
    // Compute left[i] and sumOdd[i] for i = 1..n.
    // left[i] = maximum transitions on a path that starts and ends at platform i, using only bridges to the left.
    // sumOdd[i] = sum of odd numbers for bridges 1..(i-1).
    vector<ll> left(n+1, 0), sumOdd(n+1, 0);
    left[1] = 0;
    sumOdd[1] = 0;
    for (int i = 2; i <= n; i++){
        if(a[i-1] == 1) {
            left[i] = 0;
        } else {
            left[i] = left[i-1] + even(a[i-1]);
        }
        sumOdd[i] = sumOdd[i-1] + odd(a[i-1]);
    }
    
    // Compute right[j] for j = 1..n.
    // right[j] = maximum transitions on a path that starts and ends at platform j, using only bridges to the right.
    vector<ll> right(n+1, 0);
    right[n] = 0;
    for (int j = n-1; j >= 1; j--){
        if(a[j] == 1) {
            right[j] = 0;
        } else {
            right[j] = right[j+1] + even(a[j]);
        }
    }
    
    // Now, the maximum number of transitions for a path with endpoints on platforms i and j (i<=j) is:
    // (left[i] - sumOdd[i]) + (right[j] + sumOdd[j])
    // We want to maximize that.
    ll ans = -1e18;
    ll bestPrefix = -1e18; // best value of (left[i]-sumOdd[i]) for i up to current j.
    for (int j = 1; j <= n; j++){
        bestPrefix = max(bestPrefix, left[j] - sumOdd[j]);
        ll candidate = bestPrefix + (right[j] + sumOdd[j]);
        ans = max(ans, candidate);
    }
    
    cout << ans << "\n";
    return 0;
}
