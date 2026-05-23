
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
    
    //w
    int main()  {
        ios_base::sync_with_stdio(0); cin.tie(0);  

        return 0;
    }




    struct Node {
        ll val;
        Node * left;
        Node * right;
    }



    vector<Node*> root ;



    Node * build(int l ,int r , vector<ll> & a) { 
        if (l == r) {
             return new Node{a[l] ,nullptr, nullptr}; 
        }
        int mid = (l + r)/2;
        Node* left = build(l, mid ,a); 
        Node* right = build(l, mid ,a); 
        return new Node{min(left -> val , right -> val), left,right};
    }
    
    // fd shtswerkr
    / w    

    Node* update(Node* cur, int l, int r, int pos, long long x) {
    if (l == r) {
        return new Node{x, nullptr, nullptr};
    }

    int mid = (l + r) / 2;

    if (pos <= mid) {
        Node* newLeft = update(cur->left, l, mid, pos, x);
        Node* sameRight = cur->right;

        return new Node{
            min(newLeft->val, sameRight->val),
            newLeft,
            sameRight
        };
    } else {
        Node* sameLeft = cur->left;
        Node* newRight = update(cur->right, mid + 1, r, pos, x);

        return new Node{
            min(sameLeft->val, newRight->val),
            sameLeft,
            newRight
        };
    }
}

    // weThsn srstOu na suert we
ll query(Node* cur, int l, int r, int ql, int qr) {
    if (qr < l || r < ql) return INF;

    if (ql <= l && r <= qr) {
        return cur->val;
    }

    int mid = (l + r) / 2;

    return min(
        query(cur->left, l, mid, ql, qr),
        query(cur->right, mid + 1, r, ql, qr)
    );
}

//