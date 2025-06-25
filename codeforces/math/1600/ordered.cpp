#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
    int tt;
    cin >> tt;
    while (tt--) {
        int n;
        long long k;
        cin >> n >> k;
        vector <int> a, b;
        
        if (n <= 60 && (1ll << (n - 1)) < k) {
            cout << -1 << endl;
            continue;
        }
        k--;
        vector <int> d;
        while (k) {
            d.push_back(k % 2);
            k /= 2;
        }
        while (d.size() < n - 1) d.push_back(0);
        
        for (int i = n - 2, j = 1; i >= 0; i--, j++) {
            if (d[i] == 0) a.push_back(j);
            else b.push_back(j);
        }
        
        reverse(b.begin(), b.end());
        for (int i : a) cout << i << ' ';
        cout << n << ' ';
        for (int i : b) cout << i << ' ';
        cout << endl;
    }
 
    return 0;
}