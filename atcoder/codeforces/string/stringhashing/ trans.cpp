#include <bits/stdc++.h>
using namespace std;

struct DoubleHash {
    using u32 = uint32_t; using u64 = uint64_t;
    static constexpr u32 M1 = 1000000007u, M2 = 1000000009u;
    static constexpr u32 B1 = 911382323u % M1, B2 = 972663749u % M2;

    static vector<u32> pow1, pow2;
    vector<u32> p1, p2;

    static void ensure(size_t n) {
        if (pow1.size() > n) return;
        size_t old = pow1.size();
        if (old == 0) { pow1 = {1}; pow2 = {1}; old = 1; }
        pow1.resize(n+1); pow2.resize(n+1);
        for (size_t i = old; i <= n; ++i) {
            pow1[i] = (u64)pow1[i-1] * B1 % M1;
            pow2[i] = (u64)pow2[i-1] * B2 % M2;
        }
    }
    static inline u32 sub(u32 a, u32 b, u32 M){ return a>=b? a-b : a+M-b; }

    DoubleHash() {}
    DoubleHash(const string& s) { build(s); }
    void build(const string& s) {
        ensure(s.size());
        p1.assign(s.size()+1,0); p2.assign(s.size()+1,0);
        for (size_t i=0;i<s.size();++i){
            u32 v = (unsigned char)s[i];
            p1[i+1] = ((u64)p1[i]*B1 + v) % M1;
            p2[i+1] = ((u64)p2[i]*B2 + v) % M2;
        }
    }
    // hash of s[l..r], inclusive
    pair<u32,u32> get(size_t l, size_t r) const {
        if (l>r) return {0,0};
        size_t len = r-l+1;
        u32 x1 = sub(p1[r+1], (u64)p1[l]*pow1[len]%M1, M1);
        u32 x2 = sub(p2[r+1], (u64)p2[l]*pow2[len]%M2, M2);
        return {x1,x2};
    }
};
vector<uint32_t> DoubleHash::pow1;
vector<uint32_t> DoubleHash::pow2;

static vector<int> prefix_function(const string& s){
    int n = (int)s.size();
    vector<int> pi(n,0);
    for(int i=1;i<n;++i){
        int j = pi[i-1];
        while(j>0 && s[i]!=s[j]) j = pi[j-1];
        if(s[i]==s[j]) ++j;
        pi[i]=j;
    }
    return pi;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string a,b;
    if(!getline(cin,a)) return 0;
    if(!getline(cin,b)) return 0;
    int n = (int)a.size();
    if((int)b.size()!=n){ cout << "-1 -1\n"; return 0; }

    string ar=a; reverse(ar.begin(), ar.end());
    string br=b; reverse(br.begin(), br.end());

    // LCP(a, br) to know the maximum candidate i
    int P=0; while(P<n && a[P]==br[P]) ++P;
    if(P==0){ cout << "-1 -1\n"; return 0; } // no i>=0 works

    // Build double hashers for O(1) substring checks
    DoubleHash Ha(a), Hb(b);

    // Precompute L2 for any prefix length t of b using KMP on (ar + sep + b)
    const char SEP = '\1'; // not in ASCII [32..126]
    string T; T.reserve(n+n+1);
    T.append(ar); T.push_back(SEP); T.append(b);
    auto pi = prefix_function(T);
    // sufPref[t] = length of longest prefix of ar that is suffix of b[0..t-1]
    // index in T for b's t-th char is |ar|+1 + (t-1)
    auto sufPref = [&](int t)->int{
        if(t<=0) return 0;
        return pi[(int)ar.size() + 1 + t - 1];
    };

    // Try i = P-1, P-2, ..., 0
    for(int i = P-1; i >= 0; --i){
        int L3 = i+1;                      // size of reverse(prefix) at the end of b
        int t  = n - L3;                   // length of b's prefix before that
        int L2 = sufPref(t);               // longest suffix of b[0..t-1] equal to prefix of ar
        if(L2 == 0) {                      // implies j = n (invalid), skip
            continue;
        }
        int j = n - L2;                    // minimal j for this i (we maximize L2)
        if(!(0 <= i && i < j && j < n)) continue;

        int L1 = j - i - 1;                // length of the middle block a[i+1..j-1]
        // Check middle with hashes: b[0..L1-1] == a[i+1..i+L1]
        if(L1 == 0){
            cout << i << ' ' << j << '\n';
            return 0;
        } else {
            auto hb = Hb.get(0, L1-1);
            auto ha = Ha.get(i+1, i+L1);
            if(hb == ha){
                cout << i << ' ' << j << '\n';
                return 0;
            }
        }
    }

    cout << "-1 -1\n";
    return 0;
}
