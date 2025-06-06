 
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
    int main()  {
        ios_base::sync_with_stdio(0); cin.tie(0);  
        int n; cin >> n;
        vector<int> arr(n);
        for (int i = 0 ;i < n; i ++) {
            cin >> arr[i]; 
        }
        string s;
        for(int i = 1; i < n; i++){
            if (arr[i] > arr[i-1])      s.push_back('<');
            else if (arr[i] < arr[i-1]) s.push_back('>');
            // else (arr[i]==arr[i-1]) → do nothing
        }
        char curr  = s[0];
        int count = 1; 
        
        vector<pair<char,int>> rle;         
        for (int i = 1 ; i < n - 1 ; i ++) {
            if (curr == s[i]) {
                count ++; 
            } else {
                rle.push_back({curr , count});
                count = 1; 
                curr = s[i]; 
            }          
        }
        
        rle.push_back({curr,count});
        int l = rle.size(); 
        
        ll res = 0;
        for (int i = 2 ; i < l ; i ++ )  {
            bool b1 = rle[i - 2].first == '<';
            bool b2 = rle[i - 1].first == '>';
            bool b3 = rle[i].first == '<';
            if (b1 && b2 && b3) {
                res += (rle[i - 2].second * rle[i].second);
            }
        } 
        
        cout << res << endl;
        return 0;
    }
    