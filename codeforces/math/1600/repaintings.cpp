#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;

    while(T--){
        int n;
        cin >> n;
        vector<ll> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        // w
        // Interval for sums of subarrays NOT containing the strange element:
        ll l1 = 0, r1 = 0;
        // Interval for sums of subarrays    containing the strange element:
        ll l2 = LLONG_MAX, r2 = LLONG_MIN;

        ll pr = 0;           // running prefix sum
        // Track min/max prefix sums before seeing strange element (or after freezing)
        ll mnl = 0, mxl = 0;
        // Track frozen min/max at the moment we see the strange element
        ll mnr = LLONG_MAX, mxr = LLONG_MIN;

        for(ll v : a){
            pr += v;
            // on encountering the "strange" element (not ±1), freeze
            if(v != 1 && v != -1){
                mnr = mnl;
                mxr = mxl;
                // restart trackers so further prefixes count for "with-strange"
                mnl = mxl = pr;
            }

            // update interval for subarrays NOT containing strange:
            // any sum is pr - (some previous prefix in [mnl..mxl])
            l1 = min(l1, pr - mxl);
            r1 = max(r1, pr - mnl);

            // update interval for subarrays containing strange:
            // any sum is pr - (some frozen prefix in [mnr..mxr])
            if(mnr != LLONG_MAX){ // only once we've seen the strange
                l2 = min(l2, pr - mxr);
                r2 = max(r2, pr - mnr);
            }

            // always grow the current prefix min/max
            mnl = min(mnl, pr);
            mxl = max(mxl, pr);
        }

        // Build the union of [l1..r1] and [l2..r2]
        vector<ll> res;
        // if we never saw a strange element, just output [l1..r1]
        if(l2 == LLONG_MAX){
            for(ll x = l1; x <= r1; x++) res.push_back(x);
        }
        else if(l2 > r1){
            // disjoint, no-overlap: first [l1..r1], then [l2..r2]
            for(ll x = l1; x <= r1; x++) res.push_back(x);
            for(ll x = l2; x <= r2; x++) res.push_back(x);
        }
        else if(r2 < l1){
            // disjoint the other way
            for(ll x = l2; x <= r2; x++) res.push_back(x);
            for(ll x = l1; x <= r1; x++) res.push_back(x);
        }
        else {
            // they overlap → one big interval
            ll L = min(l1, l2);
            ll R = max(r1, r2);
            for(ll x = L; x <= R; x++) res.push_back(x);
        }

        // output
        cout << res.size() << "\n";
        for(size_t i = 0; i < res.size(); i++){
            cout << res[i] << (i + 1 < res.size() ? ' ' : '\n');
        }
    }

    return 0;
}
