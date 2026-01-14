#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; ll m;
    cin >> n >> m;

    int h = n/2;
    int h2 = n - h;

    vector<ll> arr(n);
    for(int i = 0; i < n; i++)
        cin >> arr[i];

    // 1) build all sums %m of subsets of arr[0..h-1]
    int bm1 = 1 << h;
    set<ll> s1;
    for(int mask = 0; mask < bm1; mask++){
        ll sum = 0;
        for(int j = 0; j < h; j++){
            if (mask & (1<<j))
                sum = (sum + arr[j]) % m;
        }
        s1.insert(sum);
    }

    // 2) for each subset of arr[h..n-1], find the best match in s1
    ll res = 0;
    int bm2 = 1 << h2;
    for(int mask = 0; mask < bm2; mask++){
        ll sum = 0;
        for(int j = 0; j < h2; j++){
            if (mask & (1<<j))
                sum = (sum + arr[h + j]) % m;
        }
        // we want s1_val + sum < m  =>  s1_val < m - sum
        ll need = m - sum;
        auto it = s1.lower_bound(need);
        if (it == s1.begin()) {
            // no s1_val < need, best is 0 + sum
            res = max(res, sum);
        } else {
            --it;
            // combine the two halves
            ll candidate = *it + sum; 
            // candidate < m guaranteed
            res = max(res, candidate);
        }
    }

    cout << res << "\n";
    return 0;
}
