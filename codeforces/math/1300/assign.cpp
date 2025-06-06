#include <bits/stdc++.h>

using namespace std;
typedef long long LL;

const int N = 300010;
int t, n, a[N];

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

void solve() {
    unordered_map<LL, int, custom_hash> mp;
    mp[0] = 0;
    LL sum = 0;
    int ans = 0, pre = 0;
    for(int i = 1; i <= n; i++) {
        sum += a[i];
        if(mp.count(sum) && mp[sum] >= pre) {
            pre = i;
            ans++;
        }
        mp[sum] = i;
    }
    printf("%d\n", ans);
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
