#include <bits/stdc++.h>

using namespace std;

const int MAX = 11;

int main() {
    int tests;
    cin >> tests;
    for(int test = 0; test < tests; test++) {
        int n;
        cin >> n;
        vector<int> a(n);
        for(auto &i : a) {
            cin >> i;
        }
        long long ans = 0;
        for(int x = 1; x < MAX; x++) {
            vector<int> b(n);
            for(int i = 0; i < n; i++) {
                b[i] = (a[i] > x? 1 : -1);
            }
            int sum = n;
            vector<int> pref(n);
            for(int i = 0; i < n; i++) {
                pref[i] = sum;
                sum += b[i];
            }
            vector<int> cnt(2 * n + 1);
            sum = n;
            int j = 0;
            for(int i = 0; i < n; i++) {
                if(a[i] == x) {
                    while(j <= i) {
                        cnt[pref[j]]++;
                        j++;
                    }
                }
                sum += b[i];
                ans += cnt[sum];
            }
        }
        ans = 1ll * n * (n + 1) / 2 - ans;
        cout << ans << '\n';
    }
    return 0;
}

