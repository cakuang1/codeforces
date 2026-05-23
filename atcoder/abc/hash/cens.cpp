#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;
using ll = long long;



// 


struct HashedString {
    static const ll M = (1LL << 61) - 1;
    static ll B;
    static vector<ll> powB;

    vector<ll> pref;

    static ll mod_mul(ll a, ll b) {
        return (__int128)a * b % M;
    }

    HashedString(const string& s) {
        int n = s.size();
        while ((int)powB.size() <= n) {
            powB.push_back(mod_mul(powB.back(), B));
        }

        pref.assign(n + 1, 0);

        for (int i = 0; i < n; i++) {
            pref[i + 1] = ((__int128)pref[i] * B + s[i]) % M;
        }
    }

    ll get_hash(int l, int r) {
        ll len = r - l + 1;
        ll val = pref[r + 1] - mod_mul(pref[l], powB[len]);
        val %= M;
        if (val < 0) val += M;
        return val;
    }
};


mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll HashedString::B = uniform_int_distribution<ll>(1000, HashedString::M - 1)(rng);





int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string n, h;
    cin >> n >> h;

    int L = n.size();
    int H = h.size();
    if (L > H) {
        cout << 0 << '\n';
        return 0;
    }

    ull weight[26];
    for (int i = 0; i < 26; i++) {
        weight[i] = rng();
    }

    ull target_hash = 0;
    ull window_hash = 0;

    for (int i = 0; i < L; i++) {
        target_hash += weight[n[i] - 'a'];
        window_hash += weight[h[i] - 'a'];
    }

    HashedString hs(h);
    set<ll> seen;

    for (int r = L - 1; r < H; r++) {
        if (r >= L) {
            window_hash += weight[h[r] - 'a'];
            window_hash -= weight[h[r - L] - 'a'];
        }

        if (window_hash == target_hash) {
            int l = r - L + 1;
            seen.insert(hs.get_hash(l, r));
        }
    }

    cout << seen.size() << '\n';
}
// Thwer ywrcollsid wr. sontsf siw

// w