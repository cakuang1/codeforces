 
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


    int N;
    cin >> N;

    vector<long long> A(N + 1, 0);
    for (int i = 2; i <= N; i++) cin >> A[i];

    vector<vector<int>> g(N + 1);
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    // 
    vector<int> parent(N + 1, -1);
    vector<vector<int>> children(N + 1);
    vector<int> order;
    order.reserve(N);

    {
        stack<int> st;
        st.push(1);
        parent[1] = 0;
        while (!st.empty()) {
            int v = st.top();
            st.pop();
            order.push_back(v);
            for (int to : g[v]) {
                if (to == parent[v]) continue;
                parent[to] = v;
                children[v].push_back(to);
                st.push(to);
            }
        }
    }

    long long mxA = 0;
    for (int i = 2; i <= N; i++) mxA = max(mxA, A[i]);

    auto can = [&](long long X) -> bool {
        vector<int> B(N + 1, 0); // black?
        for (int v = 2; v <= N; v++) {
            B[v] = (A[v] >= X) ? 1 : 0;
        }
        // root has no value (effectively 0), so for X>0 it is white -> B[1]=0.

        vector<long long> dp(N + 1, 0);

        // process in reverse order (postorder)
        for (int idx = (int)order.size() - 1; idx >= 0; idx--) {
            int v = order[idx];
            long long sum = 0;
            for (int c : children[v]) sum += dp[c];
            long long need_before = max(sum - 1, 0LL);
            dp[v] = need_before + B[v];
        }

        // Takahashi can force reaching a black node  <=>  Aoki cannot win with 0 pre-paints  <=> dp[1] > 0
        return dp[1] > 0;
    };


    long long ok = 0;
    long long notok = mxA + 1;
    while ((notok - ok) > 1) {
        long long mid = (ok + notok)/2 ;
        if (can(mid)) {
            ok = mid; 
        } else {
            notok = mid; 
        }
    }
    cout << ok << "\n";
    return 0;
    }




    // we hworsodufwl