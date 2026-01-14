#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int MOD = 1000000007; 
const int MOD2 =  998244353; 
const ll INF = 1e18;
const int MX = 1000001; //check the limits, dummy

bitset<1000001> subsetSum(const vector<int>& cycles, int k) {
    unordered_map<int,int> cnt;
    for (int c : cycles) cnt[c]++;

    vector<int> eff; // compressed items
    for (auto [w, occ] : cnt) {
        int pow2 = 1;
        while (occ > 0) {
            int take = min(pow2, occ);
            eff.push_back(take * w);
            occ -= take;
            pow2 <<= 1;
        }
    }

    bitset<1000001> dp;
    dp[0] = 1;
    for (int w : eff) {
        dp |= (dp << w);
    }
    return dp;
}

int main()  {
    ios_base::sync_with_stdio(0); 
    cin.tie(0);  

    int n, k;
    cin >> n >> k;
    
    vector<int> arr(n);
    vector<bool> vis(n,false);
    for (int i = 0 ; i < n; i++) {
        cin >> arr[i]; 
        arr[i]--; // permutation is 1-indexed in input
    }

    vector<ll> cycles;
    for (int i = 0 ; i < n; i++) { 
        if (!vis[i]) { 
            int start = i;
            int count = 0; 
            while (!vis[start]) {
                vis[start] = true; 
                count++;
                start = arr[start]; 
            }
            cycles.push_back(count); 
        }
    }

    ll twos = 0, ones = 0;
    for (ll c : cycles) {
        twos += c / 2;
        if (c % 2) ones++;
    }

    ll twosused = min<ll>(k, twos);
    ll kleft = k - twosused;
    ll onesused = min<ll>(kleft, ones);
    ll a1 = 2 * twosused + onesused;

    auto res = subsetSum(cycles, k);
    int a2;
    if (res[k]) a2 = k;    
    else a2 = k + 1;
    
    cout << a2 << ' ' << a1 << "\n"; 
    return 0;
}
