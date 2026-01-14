    #include <bits/stdc++.h>
    using namespace std;

    using ull = unsigned long long;
    using ll  = long long;

    static inline ll mulmod(ll a, ll b, ll m) { return ( a * b ) % m; }
    static inline ll addmod(ll a, ll b, ll m) { a += b; if (a >= m) a -= m; return a; }

    int main() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);

        string s, goodMask;
        int k;
        if (!(cin >> s >> goodMask >> k)) return 0;

        const int n = (int)s.size();

        // Two moduli + two bases
        const ll M1 = 1000000007LL, M2 = 1000000009LL;
        const ll B1 = 911382323LL % M1;     // reduce base modulo
        const ll B2 = 972663749LL % M2;

        // Precompute powers up to n
        vector<ll> P1(n + 1, 1), P2(n + 1, 1);
        for (int i = 1; i <= n; ++i) {
            P1[i] = mulmod(P1[i-1], B1, M1);
            P2[i] = mulmod(P2[i-1], B2, M2);
        }

        // w 
        unordered_set<ull> seen;


        //we 
        for (int i = 0; i < n; ++i) {
            ll h1 = 0, h2 = 0;           // normalized: sum val * B^{len-1}, but we’ll just use len from 0
            int bad = 0;
            for (int j = i; j < n; ++j) {
                int idx = s[j] - 'a';               // 0..25
                if (goodMask[idx] == '0') {         // '0' means BAD in CF 271D
                    if (++bad > k) break;
                }
                int val = idx + 1;                  // map 'a'..'z' -> 1..26
                int len = j - i;                    // current exponent

                h1 = addmod(h1, mulmod(val, P1[len], M1), M1);
                h2 = addmod(h2, mulmod(val, P2[len], M2), M2);

                ull key = ( (ull)h1 << 32 ) | (ull)h2;
                seen.insert(key);
            }
        }

        cout << seen.size() << '\n';
        return 0;
    }

