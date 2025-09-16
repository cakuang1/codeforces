 
    #include <bits/stdc++.h>
    
    using namespace std;

    using ll = long long;
    const int MOD = 1000000007; 
    const int MOD2 =  998244353; 
    const ll INF = 1e18;
    const int MX = 1000001; //check the limits, dummy


    ll modExp(ll base, ll power) {
        if (power == 0) {
            return 1;
        } else {
            ll cur = modExp(base, power / 2); cur = cur * cur; cur = cur % MOD;
            if (power % 2 == 1) cur = cur * base;
            cur = cur % MOD;
            return cur;
        }
    }

    ll inv(ll base) {
        return modExp(base, MOD-2);
    }


    ll mul(ll A, ll B) {
        return (A*B)%MOD;
    }

    ll add(ll A, ll B) {
        return (A+B)%MOD;
    }
    
    ll dvd(ll A, ll B) {
        return mul(A, inv(B));
    }

    ll sub(ll A, ll B) {
        return (A-B+MOD)%MOD;
    }

    ll* facs = new ll[MX];
    ll* facInvs = new ll[MX];

    ll choose(ll a, ll b) {
        if (b > a) return 0;
        if (a < 0) return 0;
        if (b < 0) return 0;
        ll cur = facs[a];
        cur = mul(cur, facInvs[b]);
        cur = mul(cur, facInvs[a-b]);
        return cur;
    }

    void initFacs() {
        facs[0] = 1; 
        facInvs[0] = 1;
        for (int i = 1 ; i < MX ; i ++ ) {
            facs[i] = (facs[i-1] * i) % MOD;
            facInvs[i] = inv(facs[i]);
        }
    }

// Build suffix array for 's' in O(n log n) using prefix-doubling + radix (counting) sort.
// Returns SA for the ORIGINAL string (no sentinel index in the result).
vector<int> suffix_array(string s) {
    // 1) Append a sentinel smaller than all chars to end of s.
    //    This guarantees every suffix is a prefix of some cyclic shift,
    //    and makes all suffixes distinct.
    s.push_back('\0');                      // '\0' is the smallest possible char

    int n = (int)s.size();                  // length INCLUDING sentinel

    // 2) Arrays:
    //    sa : suffix order (permutation of 0..n-1)
    //    c  : equivalence class of prefix of current length for suffix starting at i
    vector<int> sa(n), c(n);

    // 3) Initial sorting by the first character (k = 0, length = 1).
    {
        // Convert characters to integers and coordinate-compress them (optional but safe).
        vector<int> vals(n);
        for (int i = 0; i < n; ++i) vals[i] = (unsigned char)s[i];

        vector<int> uniq = vals;            // unique sorted characters
        sort(uniq.begin(), uniq.end());
        uniq.erase(unique(uniq.begin(), uniq.end()), uniq.end());

        for (int i = 0; i < n; ++i)
            c[i] = int(lower_bound(uniq.begin(), uniq.end(), vals[i]) - uniq.begin());

        // Counting sort indices 0..n-1 by class c[i].
        int K = (int)uniq.size();           // number of distinct characters
        vector<int> cnt(max(K, n), 0), sa0(n);
        for (int i = 0; i < n; ++i) cnt[c[i]]++;
        for (int i = 1; i < K; ++i) cnt[i] += cnt[i-1];
        for (int i = n-1; i >= 0; --i) sa0[--cnt[c[i]]] = i;
        sa.swap(sa0);                        // now 'sa' is sorted by first character

        // Rebuild c so that it’s consistent with 'sa' order (0..classes-1)
        vector<int> c0(n);
        c0[sa[0]] = 0;
        int classes = 1;
        for (int i = 1; i < n; ++i) {
            if (s[sa[i]] != s[sa[i-1]]) ++classes;
            c0[sa[i]] = classes - 1;
        }
        c.swap(c0);
    }

    // 4) Iteratively double the length: 1, 2, 4, 8, ...
    //    At round 'h', we sort by pairs (c[i], c[i + 2^h]).
    for (int h = 0; (1 << h) < n; ++h) {
        int len = 1 << h;

        // 4a) Build the order by SECOND half already sorted:
        //     shift all indices left by 'len' so that their second half aligns with previous order
        vector<int> sa_shifted(n);
        for (int i = 0; i < n; ++i) {
            sa_shifted[i] = sa[i] - len;
            if (sa_shifted[i] < 0) sa_shifted[i] += n;
        }

        // 4b) Counting sort by FIRST key c[i] (stable), using sa_shifted as current order by second key.
        int classes = 0;
        for (int v : c) classes = max(classes, v+1); // number of classes in c
        vector<int> cnt(max(classes, n), 0), sa_new(n);
        for (int i = 0; i < n; ++i) cnt[c[sa_shifted[i]]]++;
        for (int i = 1; i < classes; ++i) cnt[i] += cnt[i-1];
        for (int i = n-1; i >= 0; --i) sa_new[--cnt[c[sa_shifted[i]]]] = sa_shifted[i];
        sa.swap(sa_new);                    // new order by pair (first, second)

        // 4c) Recompute equivalence classes for doubled length.
        vector<int> c_new(n);
        c_new[sa[0]] = 0;
        int cur = 1;
        for (int i = 1; i < n; ++i) {
            // Pair for current and previous suffix:
            pair<int,int> prev = { c[sa[i-1]], c[(sa[i-1] + len) % n] };
            pair<int,int> now  = { c[sa[i]],   c[(sa[i]   + len) % n] };
            if (now != prev) ++cur;
            c_new[sa[i]] = cur - 1;
        }
        c.swap(c_new);

        // 4d) Early stop if all ranks are unique (classes == n).
        if (cur == n) break;
    }

    // 5) Remove the sentinel (it’s always the suffix starting at n-1).
    //    Return SA for the original string.
    sa.erase(find(sa.begin(), sa.end(), n-1));
    return sa;
}


// Kasai's algorithm: build LCP array in O(n).
vector<int> lcp_array(const string& s, const vector<int>& sa) {
    int n = (int)s.size();                 // original string length (no sentinel)
    vector<int> rank(n, 0);
    for (int i = 0; i < n; ++i) rank[sa[i]] = i;
    vector<int> lcp(n, 0);
    int k = 0;                             // current matched prefix length to reuse
    for (int i = 0; i < n; ++i) {
        int r = rank[i];
        if (r == 0) {                      // first in SA has no previous neighbor
            k = 0;
            lcp[r] = 0;
            continue;
        }
        int j = sa[r - 1];                 // previous suffix in lex order
        // extend LCP by reusing k (start comparisons at k)
        while (i + k < n && j + k < n && s[i + k] == s[j + k]) ++k;
        lcp[r] = k;
        if (k > 0) --k;                    // prepare for next i+1: LCP >= k-1
    }
    return lcp;
}


    

    // shrotes erwon wei srautalmallw rclongesrwe
    // wrwhyw is that wr
    // w
    int main()  {
        ios_base::sync_with_stdio(0); cin.tie(0);  
        string s ; cin >> s ;
        int n = s.size(); 
        int m; cin >> m;
        
    
    
        for (int i = 0 ; i < m ; i ++) {
             
        }

        return 0;
    }
     


    // washenst w