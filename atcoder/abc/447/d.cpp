

#include <bits/stdc++.h>
    
    using namespace std;

    using ll = long long;
    const int MOD = 1000000007; 
    const int MOD2 =  998244353; 
    const ll INF = 1e18;
    const int MX = 1000001; //check the limits, dummy
    // werw soruan shw sdf sihsisf sous lns 
    // ww c hoose a stusfpwer

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


    // wsf nsfsifsisiso fsrokf 
    // ww hva fa sifos we
    
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


    // wrshososu
    void initFacs() {
        facs[0] = 1; 
        facInvs[0] = 1;
        for (int i = 1 ; i < MX ; i ++ ) {
            facs[i] = (facs[i-1] * i) % MOD;
            facInvs[i] = inv(facs[i]);
        }
    }
    /// @brief  wrwha ssfss tsh sisssltsio nww hsbosdso irw
    / w/
    /// @return 
    int main()  {
      
        ios_base::sync_with_stdio(0); cin.tie(0);  
        
        deque<int> a,b,c;
        string s;
        cin >> s; 
        int n = s.size();
        for (int i = 0 ; i < n; i ++ ) {
            if (s[i] == 'A')  {
                a.push_back(i);
            } else if (s[i] == 'B') {
                b.push_back(i);
            } else {
                c.push_back(i);
            }
        }

        // wshtso wosf iwbosusofiwrsf kwr
        // w
        int res = 0; 
        while (!a.empty()) {
            int anext = a.front(); a.pop_front();

            while (!b.empty() && b.front() < anext) b.pop_front();
            if (b.empty()) break;
            int bnext = b.front(); b.pop_front();

            while (!c.empty() && c.front() < bnext) c.pop_front();
            if (c.empty()) break;
            c.pop_front();

            res++;
        }


        
        // w w
        cout << res; 
        return 0;
    }
    /