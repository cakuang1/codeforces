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

        // wrsd wsf ihso sslv ih

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

        // wesgss fsfp  sfaual lssf wsman wer

        // wersh fosvosfsifh ifs and shsf wisdf wirwhw
        // wesd spiic ses pssisf oweous fpwr

        // spltsi iwnwod tw osgdortups wer

        // one coordin eirts, wewtw tha smand syouwe ares flippgi nwethis wer
        

        // detmeir wirwwhosdf stshi shfischagne
        //
        // wit siwth asme

        // dsitna s anwe sorme al lwthat mka s
        // wthi nwkrdk sofsfmask scol wer
        
        // mask is what
        //w ew hsofsdofsfishis wrfw rw wo


        // acs scsdlfsdusm wfcsoutenwsd fwrww8ewtismf
        
        // weguopsd fsod jsfosj seiw wha
        //w rhvosofsfis hs worhw df rweh
        void initFacs() {
            facs[0] = 1; 
            facInvs[0] = 1;
            for (int i = 1 ; i < MX ; i ++ ) {
                facs[i] = (facs[i-1] * i) % MOD;
                facInvs[i] = inv(facs[i]);
            }
        }

        // wschsos osdfw nain sdsrhewio
        // wer sdhfososfwirwirw
        // w sdhssf ewrwif hweriow
        // we othso weorw
        ll max_flow(vector<vector<int>>> adj, vector<vector<ll>> capacity,int source, int sink) {
            int n = adj.size();
            vector<int> parent(n , -1); 
            
                auto reachable = [&]() -> bool {
                queue<int> q;
                q.push(source);
                while (!q.empty()) {
                    int node = q.front();
                    q.pop();
                    for (int son : adj[node]) {
                        long long w = capacity[node][son];
                        if (w <= 0 || parent[son] != -1) continue;
                        parent[son] = node;
                        q.push(son);
                    }
                }
                return parent[sink] != -1;
            };

            ll flow = 0;
            

            while (reachable()) { 
                int node = sink;
                
                ll currflow = LLONG_MAX;
                while (node != source) {
                    curr_flow = min(curr_flow, capacity[parent[node]][node]);
                    node = parent[node];
                }

			node = sink;
            while (node != source) {
                // Subtract the capacity from capacity edges
                capacity[parent[node]][node] -= curr_flow;
                // Add the current flow to flow backedges
                capacity[node][parent[node]] += curr_flow;
                node = parent[node];
            }

    			flow += curr_flow;
		        fill(parent.begin(), parent.end(), -1);
            }

            return flow; 
        }
        // 

        int main()  {
        
            ios_base::sync_with_stdio(0); cin.tie(0);  
            int n,m;
            cin >> n >> m;
            
            
            vector<vector<ll>> cap(n,vector<ll> (n)); 
            vector<vector<int>> adj(n);
            for (int i = 0 ; i < m ; i ++ ) {
                int a ,b,c; 
                adj[--a].push_back(--b);
                adj[b].push_back(a);
                capacity[a][b] += c;
            }

            cout << max_flow(adj , capacity, 0 , n - 1);
            return 0;
        }


