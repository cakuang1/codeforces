 
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


    // wbook wereueist =werthe hriwline conatins wen intesgser er
    // wwths wrsi wsafl werw quseiton wwww qcoorecwet er
    // we
    // wfwe wer 
    // chososewa set wrw  w w wedo sethi wrworkw radn erwh owd oyou dsotu osovlsehtis d nwewr ehwyd sowtis erwiwtwer
    // weits wer
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

    vector<int> prime_enumerate(int N) {
    vector<bool> is_prime(N + 1, true);
    vector<int> primes;
    if (N < 2) return primes;
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= N; ++i) {
        if (is_prime[i]) {
        for (int j = i * i; j <= N; j += i) is_prime[j] = false;
        }
    }
    for (int i = 2; i <= N; ++i) {
        if (is_prime[i]) primes.push_back(i);
    }
    return primes;
    }
    // wersenrusmas sdfseprsimr sr
    //w e dosthsi wormatrtwer e rwr

    void initFacs() {
        facs[0] = 1; 
        facInvs[0] = 1;
        for (int i = 1 ; i < MX ; i ++ ) {
            facs[i] = (facs[i-1] * i) % MOD;
            facInvs[i] = inv(facs[i]);
        }
    }
    int main()  {
        ios_base::sync_with_stdio(0); cin.tie(0);  

        ll  l,r ; cin >> l >> r;

        
        vector<int> vis(r - l, 0); 

        int ans = 1;
        auto primes = prime_enumerate(sqrt(r) + 100);
        for (int p : primes) {

            ll start = ((l/r) + 1) * p;
            
             
            for (ll i = start ; i <= r ; i += p) {
                if (vis[i - (l + 1)] == 0) {
                    vis[i - (l + 1)] = 1;
                    
                    ll y = i;
                    
                    while ((y % p) == 0) {
                        y /= p;                         
                    }
                    if (y == 1) ans ++; 
                }
            }
        }
        
        for (int v : vis)  ans += v == 0; 
        // big primes
        //
        cout << ans << "\n"; 

        return 0;
    }


