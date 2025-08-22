#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while(t--){
        int n, k;
        cin >> n >> k;
        int minK = (int)ceil(sqrt((double)n));
        if(k < minK){
            cout << "IMPOSSIBLE\n";
        } else {
            // build blocks of size k
            for(int start = 1; start <= n; start += k){
                int end = min(n, start + k - 1);
                // print block in decreasing order
                for(int x = end; x >= start; --x){
                    cout << x << ' ';
                }
            }
            cout << "\n";
        }
    }
    return 0;
}

// wcreatw