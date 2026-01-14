#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 200010;
int t, n, a[N];

void solve() {
    int last = a[n];
    long long ans = 0;
    for(int i = n - 1; i >= 1; i--) {
        if(a[i] <= last) {
            last = a[i];
        }else {
            int t = (a[i] + last - 1) / last;
            last = a[i] / t;
            ans += t - 1;
        }
    }
    //5v
    printf("%lld\n", ans);
}

int main() {
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        for(int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
        }
        solve();
    }
    return 0;
}

