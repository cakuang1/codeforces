#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

int main(){
    ll n;
    cin >> n;
    
    vector<ll> funValues;
    
    // Loop over all possible divisors.
    for (ll i = 1; i * i <= n; i++){
        if (n % i == 0) {
            // First divisor: d = i
            ll d = i;
            ll L = n / d; // cycle length
            ll F = L + d * (L * (L - 1) / 2); // fun value for divisor d
            funValues.push_back(F);
            
            // Check if the complementary divisor is different.
            if (i * i != n) {
                d = n / i;
                L = n / d;
                F = L + d * (L * (L - 1) / 2);
                funValues.push_back(F);
            }
        }
    }
    
    // Sort the fun values in increasing order.
    sort(funValues.begin(), funValues.end());
    
    // Output the fun values.
    for (ll F : funValues)
        cout << F << " ";
    cout << "\n";
    
    return 0;
}
