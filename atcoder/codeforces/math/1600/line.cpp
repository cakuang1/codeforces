#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int TC;
    cin >> TC;
    cout << fixed << setprecision(6);
    while(TC--){
        int n;
        cin >> n;

        vector<ll> x(n), t(n);
        for(int i = 0; i < n; i++){
            cin >> x[i];
        }
        for(int i = 0; i < n; i++){
            cin >> t[i];
        }

        // Compute A = max(x[i] + t[i]), B = min(x[i] - t[i])
        ll A = LLONG_MIN, B = LLONG_MAX;
        for(int i = 0; i < n; i++){
            A = max(A, x[i] + t[i]);
            B = min(B, x[i] - t[i]);
        }

        // The unique optimal meeting point:
        double x0 = (A + B) * 0.5;
        cout << x0 << "\n";
    }
    return 0;
}

 
  