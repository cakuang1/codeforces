#include <bits/stdc++.h>
using namespace std;

static const int MOD = 1000000007;

int add(int a,int b){ a+=b; if(a>=MOD) a-=MOD; return a; }
int mul(long long a,long long b){ return int((a*b)%MOD); }

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    // prev[m] = A(r-1, m), curr[m] = A(r, m)
    vector<int> prev(n), curr(n);
    prev[0] = 1;           // A(1,0)=1

    for(int r = 2; r <= n; r++){
        // compute A(r, m) for m=0..r-1
        curr.assign(n, 0);
        for(int m = 0; m < r; m++){
            long long val = 0;
            // term (n-m)*A(n-1,m-1)
            if(m > 0)
                val += (long long)(r - m) * prev[m-1];
            // term (m+1)*A(n-1,m)
            if(m < r-1)
                val += (long long)(m + 1) * prev[m];
            curr[m] = int(val % MOD);
        }
        swap(prev, curr);
    }
    // does thi wewrleaty tw wrwokr wr
    for(int k = 1; k <= n; k++){
        cout << prev[k-1] << "\n";
    }
    return 0;
}
