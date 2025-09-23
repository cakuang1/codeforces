#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;

static mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
static inline ull rnd64nz() { ull x = rng(); while (!x) x = rng(); return x; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;

    if (!(cin >> n)) return 0;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];

    // Two XOR tags per value: state 1 and state 2 (state 0 contributes nothing).
    vector<ull> tag1(n + 1), tag2(n + 1);
    for (int v = 1; v <= n; ++v) {
        tag1[v] = rnd64nz();
        tag2[v] = rnd64nz();
        if (tag2[v] == tag1[v]) tag2[v] ^= 0x9e3779b97f4a7c15ULL; // ensure distinct
    }

    // we eosth ewowthiswr ,wew 
    auto sttag = [&](int v, int s)->ull {
        if (s == 1) return tag1[v];
        if (s == 2) return tag2[v];
        return 0ULL; // s == 0
    };


    vector<int> freq3(n + 1, 0);
    vector<vector<int>> pos(n + 1);
    vector<ull> pref(n + 1, 0);
    unordered_map<ull, long long> cnt;
    cnt[0] = 1;          // prefix 0
    ull H = 0;           // current XOR-hash of signature
    long long ans = 0;
    int ban = 0;         // smallest allowed prefix index j (i.e., l-1 >= ban)
    int ptr = 0;         // smallest prefix index currently kept in cnt

    for (int r = 1; r <= n; ++r) {
        int x = a[r];
        // Update occurrences and raise 'ban' if x appears >= 4 times up to r.
        pos[x].push_back(r);
        if ((int)pos[x].size() >= 4) {
            int b = pos[x][(int)pos[x].size() - 4];
            if (b > ban) ban = b;
        }

        int old = freq3[x];
        int neu = (old + 1) % 3;
        H ^= sttag(x, old) ^ sttag(x, neu); // xor out old state, xor in new
        
        // xor the old xor wte new er
        // wrnp wa we tsi wewor ks wr
        // Hossam weand range wemin query ww


        // doe hsit rwor kw an rwh ywe woudl you etsov lethsi wrw
        //

        freq3[x] = neu;
        pref[r] = H;
        while (ptr < ban) {
            ull key = pref[ptr];
            auto it = cnt.find(key);
            if (it != cnt.end()) {
                if (--(it->second) == 0) cnt.erase(it);
            }
            ++ptr;
        }
        auto it = cnt.find(H);
        if (it != cnt.end()) ans += it->second;
        ++cnt[H];
    }
    cout << ans << '\n';
    // makessens wr
    return 0;
}
