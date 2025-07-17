#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n+1);
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }

    // Fenwick tree (BIT) storing counts mod 2
    vector<int> fenw(n+1, 0);
    auto add = [&](int i){
        for(; i <= n; i += i & -i)
            fenw[i] ^= 1;
    };
    auto sum = [&](int i){
        int s = 0;
        for(; i > 0; i -= i & -i)
            s ^= fenw[i];
        return s;
    };

    // Compute inversion parity of 'a'
    int inv_parity = 0;
    for(int i = 1; i <= n; i++){
        int s = sum(a[i]);            // parity of # seen ≤ a[i]
        int inv_here = ((i-1) & 1) ^ s;  // parity of # seen > a[i]
        inv_parity ^= inv_here;       
        add(a[i]);
    }

    // Petr does 3n swaps ⇒ parity = n mod 2
    // Alex does 7n+1 ⇒ parity = (7n+1) mod 2 = (n+1) mod 2
    // They differ, so compare inv_parity to n&1
    if(inv_parity == (n & 1))
        cout << "Petr\n";
    else
        cout << "Um_nik\n";

    return 0;
}

