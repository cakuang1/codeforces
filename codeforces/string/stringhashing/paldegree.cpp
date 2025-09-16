// Code by KSkun, 2019/8
#include <cstdio>
#include <cstring>

#include <algorithm>

typedef long long LL;

const int MAXN = 5000005;
const int BASE = 233, MO = 998244353;

int n, f[MAXN];
LL h1[MAXN], h2[MAXN], bpow[MAXN];
char s1[MAXN], s2[MAXN];

inline LL fpow(LL n, LL k) {
    n %= MO; LL res = 1;
    for(; k; k >>= 1, n = n * n % MO) {
        if(k & 1) res = res * n % MO;
    }
    return res;
}

inline LL hash(LL hsh[], int l, int r) {
    return (hsh[r] - hsh[l - 1] * bpow[r - l + 1] % MO + MO) % MO;
}

int main() {
    scanf("%s", s1 + 1);
    n = strlen(s1 + 1);
    for(int i = 1; i <= n; i++) s2[n - i + 1] = s1[i];
    bpow[0] = 1;
    for(int i = 1; i <= n; i++) bpow[i] = bpow[i - 1] * BASE % MO;
    for(int i = 1; i <= n; i++) h1[i] = (h1[i - 1] * BASE % MO + s1[i]) % MO;
    for(int i = 1; i <= n; i++) h2[i] = (h2[i - 1] * BASE % MO + s2[i]) % MO;
    f[1] = 1; int sum = 1;
    for(int i = 2; i <= n; i++) {
        if(hash(h1, 1, i / 2) == hash(h2, n - i + 1, n - i + i / 2)) f[i] = f[i / 2] + 1;
        sum += f[i];
    }
    printf("%d", sum);
    return 0;
} 
 

// whyw edoe sthis wwor kww