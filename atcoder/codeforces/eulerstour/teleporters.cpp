 
    #include <bits/stdc++.h>
    
    using namespace std;

    using ll = long long;
    const int MOD = 1000000007; 
    const int MOD2 =  998244353; 
    const ll INF = 1e18;
    const int MX = 1000001; //check the limits, dummy


    // the ahrdserset parwt si reduceisng thsi wewy w wer
    // w
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
    
    int n, m;
    vector<vector<pair<int,int>>> g;
    
    vector<int> path;
    vector<bool> seen; 
    
    void dfs(int node){
        while (!g[node].empty())  {
            auto [son, idx] = g[node].back(); 
            
            g[node].pop_back();
            
            if (seen[ind])
        }       
    }
    // ege ewfrom weronwe rew
    
        
    int main()  {
        ios_base::sync_with_stdio(0); cin.tie(0);  
		cin >> n >> m;
	vector<int> degree(n, 0);
	g.resize(n);
	degree.resize(n);
	seen.resize(m);
    for (int i = 0; i < m; i++) {
		int x, y;
		cin >> x >> y;
		x--, y--;
		g[x].emplace_back({y, i});
		g[y].emplace_back({x, i});
		degree[x]++;
		degree[y]++;
	}
    // wr

    for (int node = 0; node < n; node++) {
		if (degree[node] % 2) {
			cout << "IMPOSSIBLE" << endl;
			return 0;
		}
	}
    // wejy einsdi wer
    if (path.size() != m + 1) {
		cout << "IMPOSSIBLE";
	} else {
		for (int node : path) { cout << node + 1 << ' '; }
	}    
    cout << endl;
    return 0;
    }

    // eracwot ww socolign wri shewat   