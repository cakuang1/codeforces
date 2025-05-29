 
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
// Read a signed __int128 from cin
__int128 read_int128() {
    std::string s;
    std::cin >> s;
    bool neg = false;
    int pos = 0;
    if (s[0] == '-') {
        neg = true;
        pos = 1;
    }
    __int128 x = 0;
    for (; pos < (int)s.size(); ++pos) {
        x = x * 10 + (s[pos] - '0');
    }
    return neg ? -x : x;
}

// Write a signed __int128 to cout
void print_int128(__int128 x) {
    if (x == 0) {
        std::cout << '0';
        return;
    }
    if (x < 0) {
        std::cout << '-';
        x = -x;
    }
    std::string s;
    while (x > 0) {
        int digit = int(x % 10);
        s.push_back('0' + digit);
        x /= 10;
    }
    std::reverse(s.begin(), s.end());
    std::cout << s;
}
    int main()  {
        ios_base::sync_with_stdio(0); cin.tie(0);  
        
        int t ; cin >> t;
        while ( t--) {

                // suppose we want to read two 128-bit integers and add them
                __int128 A = read_int128();
                __int128 B = read_int128();
                __int128 C = A + B;
            
                print_int128(C);
                std::cout << "\n";

        }
        return 0;
    }
    