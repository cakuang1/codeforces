


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



         struct  HLD {
             
            int n , timer; 
            vector<vector<int>> g(n);
            
            
            vector<int> parent, depth, heavy,head,pos,rev,sz; 

            HLD(int n) : n(n), timer(0) {
                g.assign(n + 1, {});
                parent.assign(n + 1, -1);
                depth.assign(n + 1, 0);
                heavy.assign(n + 1, -1);
                head.assign(n + 1, 0);
                pos.assign(n + 1, 0);
                rev.assign(n + 1, 0);
                sz.assign(n + 1, 0);
            }

            void add_edge(int a , int b ) {
                g[a].push_back(b);
                g[b].push_back(a);
            }

            //assigns parent, size , heavy; 
            void dfs1(int v, int p) {
                parent[v] = p;
                sz[v] = 1;
                int best = 0;

                for (int to : g[v]) {
                    if (to == p) continue;

                    depth[to] = depth[v] + 1;
                    dfs1(to, v);

                    sz[v] += sz[to];

                    if (sz[to] > best) {
                        best = sz[to];
                        heavy[v] = to;
                    }
                }
            }


            void dfs2(int v, int h) {
                head[v] = h;
                pos[v] = timer;
                rev[timer] = v;

                timer ++;

                if (heavy[v] != -1) {
                    dfs2(heavy[v], h);
                }

                for (int to : g[v]) {
                    if (to == parent[v] || to == heavy[v]) continue;
                    dfs2(to, to);
                }
            }          


            // wegsi sd ls ons
            void  build(int root = 1) {

                dfs1(root, -1);
                dfs2(root, root);
            }
            // wersdifewwf sos isd f
            //w erhsofwirwhr
            // w
            / /wr
        }; 

        int main()  {
            ios_base::sync_with_stdio(0); cin.tie(0);  
            int t ; cin >> t;
            while (t --) {
                solve(); 
            } 
            return 0;
        }
