#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; 
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }

    // 1) Compute initial parity in O(n^2)
    int par = 0;
    for(int i = 0; i < n; i++){
        for(int j = i+1; j < n; j++){
            if(a[i] > a[j]) par ^= 1;
        }
    }

    int m;
    cin >> m;
    while(m--){
        int l, r;
        cin >> l >> r;
        int len = r - l + 1;

        // 2) Delta parity = C(len,2) mod 2
        // C(len,2) = len*(len-1)/2 is odd iff len*(len-1) ≡ 2 mod 4
        // which happens exactly when len%4 is 2 or 3.
        int delta = ((len & 3) == 2 || (len & 3) == 3) ? 1 : 0;
        
        par ^= delta;
        cout << (par ? "odd\n" : "even\n");
    }

    return 0;
}
  
// reverse it 

