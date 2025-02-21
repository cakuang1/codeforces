#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long LL;

const int N = 100010, MOD = 1e9 + 7;
int n;
char s[N], t[N];

int fast_power(int a, int b) {
    int res = 1 % MOD;
    while(b) {
        if(b & 1) res = (LL)res * a % MOD;
        a = (LL)a * a % MOD;
        b >>= 1;
    }
    return res;
}


int main() {
    scanf("%d", &n);
    scanf("%s", s + 1);
    scanf("%s", t + 1);
    int scnt = 0, tcnt = 0;
    int t1 = 0, t2 = 0;
    for(int i = 1; i <= n; i++) {
        if(s[i] != '?' && t[i] != '?') {
            if(s[i] < t[i]) t1++;
            if(s[i] > t[i]) t2++;
        }
        if(s[i] == '?') scnt++;
        if(t[i] == '?') tcnt++;
    }
    if(t1 > 0 && t2 > 0) {
        printf("%d\n", fast_power(10, scnt + tcnt));
    }else if(t1 > 0) {
        // 让所有s[i]<=t[i]
        int res = 1;
        for(int i = 1; i <= n; i++) {
            if(s[i] == '?' && t[i] == '?') {
                res = (LL)res * 55 % MOD;
            }else if(s[i] == '?') {
                res = (LL)res * (t[i] - '0' + 1) % MOD;
            }else if(t[i] == '?') {
                res = (LL)res * ('9' - s[i] + 1) % MOD;
            }
        }
        res = (fast_power(10, scnt + tcnt) - res + MOD) % MOD;
        printf("%d\n", res);
    }else if(t2 > 0) {
        // 让所有s[i]>=t[i]
        int res = 1;
        for(int i = 1; i <= n; i++) {
            if(s[i] == '?' && t[i] == '?') {
                res = (LL)res * 55 % MOD;
            }else if(s[i] == '?') {
                res = (LL)res * ('9' - t[i] + 1) % MOD;
            }else if(t[i] == '?') {
                res = (LL)res * (s[i] - '0' + 1) % MOD;
            }
        }
        res = (fast_power(10, scnt + tcnt) - res + MOD) % MOD;
        printf("%d\n", res);
    }else {
        if(scnt + tcnt < 2) {
            puts("0");
        }else {
            int less = 1, great = 1, equal = 1;
            for(int i = 1; i <= n; i++) {
                if(s[i] == '?' && t[i] == '?') {
                    less = (LL)less * 55 % MOD;
                    great = (LL)great * 55 % MOD;
                    equal = (LL)equal * 10 % MOD;
                }else if(s[i] == '?') {
                    less = (LL)less * (t[i] - '0' + 1) % MOD;      // s[i]<=t[i]
                    great = (LL)great * ('9' - t[i] + 1) % MOD;    // s[i]>=t[i]
                }else if(t[i] == '?') {
                    less = (LL)less * ('9' - s[i] + 1) % MOD;      // s[i]<=t[i]
                    great = (LL)great * (s[i] - '0' + 1) % MOD;    // s[i]>=t[i]
                }
            }
            printf("%d\n", (((fast_power(10, scnt + tcnt) - less + MOD) % MOD - great + MOD) % MOD + equal) % MOD);
        }
    }
    return 0;
}
