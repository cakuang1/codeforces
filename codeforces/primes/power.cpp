#include <bits/stdc++.h>
using namespace std;

// A signature: list of (prime, residue) pairs, in strictly increasing prime order.
using Sig = vector<pair<int,int>>;

// Fast custom hash for Sig
struct SigHash {
    size_t operator()(Sig const& s) const noexcept {
        size_t h = s.size();
        for (auto &pr : s) {
            // mix the two 32-bit ints into one 64-bit, then hash
            uint64_t key = (uint64_t(pr.first) << 32) | uint32_t(pr.second);
            h ^= std::hash<uint64_t>()(key)
                 + 0x9e3779b97f4a7c15ULL
                 + (h<<6) + (h>>2);
        }
        return h;
    }
};
struct SigEq {
    bool operator()(Sig const&a, Sig const&b) const noexcept {
        return a==b;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    int Amax = 0;
    for(int i = 0; i < n; i++){
        cin >> a[i];
        Amax = max(Amax, a[i]);
    }

    // 1) Build SPF sieve up to Amax
    vector<int> spf(Amax+1,0);
    for(int i = 2; i*i <= Amax; i++){
        if(!spf[i]){
            for(int j = i*i; j <= Amax; j += i)
                if(!spf[j]) spf[j] = i;
        }
    }
    for(int i = 2; i <= Amax; i++)
        if(!spf[i]) spf[i] = i;

    // 2) Map signatures to counts
    unordered_map<Sig,int,SigHash,SigEq> freq;
    freq.reserve(n*2);
    freq.max_load_factor(0.25f);

    long long ans = 0;
    for (int x0 : a) {
        int x = x0;
        Sig sig, comp;
        // Factor x, building sig and comp in sorted order
        while (x > 1) {
            int p = spf[x], cnt = 0;
            while (x % p == 0) {
                x /= p;
                cnt++;
            }
            int r = cnt % k;
            if (r) {
                sig.emplace_back(p, r);
                comp.emplace_back(p, k - r);
            }
        }
        // No sorts needed—spf factoring gave us increasing p already.

        // All previous a_j whose signature == comp will pair with this one.
        auto it = freq.find(comp);
        if (it != freq.end())
            ans += it->second;

        // Record our signature for future matches
        freq[sig]++;
    }
    
    cout << ans << "\n";
    return 0;
}
