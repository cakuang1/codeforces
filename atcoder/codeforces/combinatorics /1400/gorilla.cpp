#include <bits/stdc++.h>
 
#define int long long
 
using namespace std;
 
#define MAXW 200200
#define MAXNM 200200
 
int n, m, k, w, p;
int arr[MAXW], prr[MAXNM];
 
static inline int calcc(int i, int j) {
    int upr = min(i, n - k);
    int leftr = min(j, m - k);
    int upl = max(-1LL, i - k);
    int leftl = max(-1LL, j - k);
    return (upr - upl) * (leftr - leftl);
}
 
void build() {
    sort(arr, arr + w);
    reverse(arr, arr + w);
    p = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            prr[p++] = calcc(i, j);
    sort(prr, prr + p);
    reverse(prr, prr + p);
}
 
int solve() {
    int sum = 0;
    for (int i = 0; i < w; ++i)
        sum += prr[i] * arr[i];
    return sum;
}
 

 // how to see thsi 
signed main() {
    int t; cin >> t;
    while (t--) {
        cin >> n >> m >> k >> w;
        for (int i = 0; i < w; ++i)
            cin >> arr[i];
        build();
        cout << solve() << endl;
    }
}