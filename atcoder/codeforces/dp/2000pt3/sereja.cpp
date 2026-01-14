
    #include <bits/stdc++.h>
    
    using namespace std;

    using ll = long long;
    const ll MOD = 1000000007; 
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
        for (int i = 1 ; i < MOD ; i ++ ) {
            facs[i] = (facs[i-1] * i) % MOD;
            facInvs[i] = inv(facs[i]);
        }
    }


struct SegTree {
    int n;
    vector<ll> tree;
    
    SegTree(int n) : n(n) {
        tree.assign(4 * n, 0);
    }
    
    // Recursively update position pos by adding value.
    void update(int pos, ll value, int idx, int l, int r) {
        if(l == r) {
            tree[idx] = (tree[idx] + value) % MOD;
            return;
        }
        int mid = (l + r) / 2;
        if(pos <= mid)
            update(pos, value, 2*idx, l, mid);
        else
            update(pos, value, 2*idx+1, mid+1, r);
        tree[idx] = (tree[2*idx] + tree[2*idx+1]) % MOD;
    }
    
    void update(int pos, ll value) {
        update(pos, value, 1, 1, n);
    }
    
    // Query the sum in the range [ql, qr].
    ll query(int ql, int qr, int idx, int l, int r) {
        if(ql > r || qr < l)
            return 0;
        if(ql <= l && r <= qr)
            return tree[idx] % MOD;
        int mid = (l + r) / 2;
        ll leftSum = query(ql, qr, 2*idx, l, mid);
        ll rightSum = query(ql, qr, 2*idx+1, mid+1, r);
        return (leftSum + rightSum) % MOD;
    }
    
    ll query(int ql, int qr) {
        return query(ql, qr, 1, 1, n);
    }
}; 

    int main() {
        ios_base::sync_with_stdio(0); cin.tie(0);    
        int n; cin >> n; 
        
        vector<ll> arr(n);
        for (int i = 0 ; i < n; i ++) {
            cin >> arr[i]; 
        }
        vector<ll> weights(n + 1,0 );
        SegTree st(1000005);
        vector<ll> last(1000005, -1);  
    for (int i = 0; i < n; i ++) {
        ll val = arr[i]; 
        // Compute the new contribution for this occurrence:
        ll temp = (val + (val * st.query(1, val)) % MOD) % MOD;
        ll weight = temp;
        if (last[val] != -1){ 
            weight = sub(weight, weights[last[val]]);
        }     
        weights[i + 1] = weight; 
        // Update the segment tree at position val by adding 'weight'
        st.update(val, weight); 
        last[val] = i;        
    }

        ll res = 0;
        for (int i = 0 ; i < n + 1 ; i ++) {
            res = add(res ,weights[i]);
        }
        cout << res << endl; 
        return 0;
    }


    

    
