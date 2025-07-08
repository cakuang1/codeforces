#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, k;
    cin >> n >> k;
    vector<ll> arr(n);
    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }

    // freq map over the current window
    unordered_map<ll,int> freq;
    freq.reserve(k*2);
    freq.max_load_factor(0.7f);

    // build initial window [0..k-1]
    for(int i = 0; i < k; i++){
        freq[arr[i]]++;
    }

    vector<int> res;
    res.reserve(n - k + 1);
    res.push_back((int)freq.size());

    // slide the window
    for(int i = k; i < n; i++){
        ll out = arr[i-k];
        ll in  = arr[i];

        // remove outgoing
        if(--freq[out] == 0) {
            freq.erase(out);
        }
        // add incoming
        freq[in]++;

        res.push_back((int)freq.size());
    }

    // output
    for(int i = 0; i < (int)res.size(); i++){
        cout << res[i] << (i+1 < (int)res.size() ? ' ' : '\n');
    }

    return 0;
}
