#include <bits/stdc++.h>

#define forn(i, n) for (int i = 0; i < int(n); i++)

using namespace std;

long long C[20][20];
long long pw[4];

long long cnk(int n, int k){
    if (k < 0 || k > n) return 0;
    return C[n][k];
}

long long get(int n, int lft){
    long long tot = 0;
    forn(i, lft + 1)
        tot += cnk(n, i) * pw[i];
    return tot;
}

long long calc(long long x){
    string s = to_string(x);
    
    long long res = 0;
    int cur = 3;
    int n = s.size();
    
    forn(i, n){
        if (s[i] == '0') continue;
        res += get(n - i - 1, cur);
        --cur;
        if (cur == -1) break;
        res += get(n - i - 1, cur) * (s[i] - '1');
    }
    
    return res;
}

int main() {
    forn(i, 20){
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; ++j)
            C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
    }
    pw[0] = 1, pw[1] = 9, pw[2] = 81, pw[3] = 729;
    int T;
    scanf("%d", &T);
    forn(i, T){
        long long L, R;
        scanf("%lld%lld", &L, &R);
        printf("%lld\n", calc(R + 1) - calc(L));
    }
    return 0;
}