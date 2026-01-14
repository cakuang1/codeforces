 
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

    int  main()  {
        ios_base::sync_with_stdio(0); cin.tie(0);  
        int n,m; cin >> n >> m; 
        int queue<int> q;
    
        // wesd hrw owr worwrwi sdwrsd irsoi hweorw 
        vector<int> deg(); 
        // wesdf htsi worw
        for (int i = 0  ;i < n; i ++) {
            if (deg[i] == 1) {
                q.push(i);                 
            }
        }
        while (q.empty() == false) {
            int f = q.front();
            cycle[f] =#include <bits/stdc++.h>
using namespace std;

struct SegTreeFlip {
    int n;
    struct Node {
        int sum = 0;      // number of ones
        bool flip = false;
    };
    vector<Node> st;

    SegTreeFlip() : n(0) {}
    SegTreeFlip(int n_) { init(n_); }

    void init(int n_) {
        n = n_;
        st.assign(4*n + 5, {});
    }

    void apply_flip(int p, int len) {
        st[p].sum = len - st[p].sum;
        st[p].flip = !st[p].flip;
    }

    void push(int p, int l, int r) {
        if (!st[p].flip || l == r) return;
        int m = (l + r) >> 1;
        apply_flip(p<<1, m - l + 1);
        apply_flip(p<<1|1, r - (m+1) + 1);
        st[p].flip = false;
    }

    void range_flip(int p, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) {
            apply_flip(p, r - l + 1);
            return;
        }
        push(p, l, r);
        int m = (l + r) >> 1;
        range_flip(p<<1, l, m, ql, qr);
        range_flip(p<<1|1, m+1, r, ql, qr);
        st[p].sum = st[p<<1].sum + st[p<<1|1].sum;
    }

    void flip(int l, int r) {
        if (l > r) return;
        range_flip(1, 0, n-1, l, r);
    }

    int all_sum() const {
        return st[1].sum;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n+1);
    vector<pair<int,int>> edges;
    edges.reserve(n);

    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
        edges.push_back({a,b});
    }

    // 1) Find cycle vertices by leaf-pruning
    vector<int> deg(n+1);
    for (int i = 1; i <= n; i++) deg[i] = (int)g[i].size();

    queue<int> q;
    vector<char> inCycle(n+1, true);
    for (int i = 1; i <= n; i++) {
        if (deg[i] == 1) q.push(i);
    }
    while (!q.empty()) {
        int v = q.front(); q.pop();
        inCycle[v] = false;
        for (int to : g[v]) {
            if (!inCycle[to]) continue;
            deg[to]--;
            if (deg[to] == 1) q.push(to);
        }
    }

    vector<int> cycleNodes;
    for (int i = 1; i <= n; i++) if (inCycle[i]) cycleNodes.push_back(i);
    int k = (int)cycleNodes.size();

    // 2) Build an ordered cycle array cyc[0..k-1] by walking along cycle
    // Pick any cycle node as start
    int start = cycleNodes[0];
    // Find its two cycle neighbors
    vector<int> cyc;
    cyc.reserve(k);

    int prev = 0, cur = start;
    while (true) {
        cyc.push_back(cur);
        int nxt = 0;
        for (int to : g[cur]) {
            if (!inCycle[to]) continue;
            if (to == prev) continue;
            nxt = to;
            break;
        }
        if (nxt == 0) {
            // means only neighbor is prev, so we must go back to start if cycle length 2 (not possible here)
            break;
        }
        prev = cur;
        cur = nxt;
        if (cur == start) break;
        if ((int)cyc.size() > k+2) break; // safety
    }
    // The walk above returns to start and includes start again; remove last if so.
    if (!cyc.empty() && cyc.back() == start) cyc.pop_back();
    // If we somehow didn't get all k nodes (rare due to neighbor choice), do a safer walk:
    if ((int)cyc.size() != k) {
        cyc.clear();
        cyc.reserve(k);
        // Safer: start, choose one neighbor, walk until back.
        int a = start;
        int nb1 = 0, nb2 = 0;
        for (int to : g[a]) if (inCycle[to]) { if (!nb1) nb1 = to; else nb2 = to; }
        int firstNext = nb1;
        prev = a;
        cur = firstNext;
        cyc.push_back(a);
        while (cur != start) {
            cyc.push_back(cur);
            int nxt = 0;
            for (int to : g[cur]) {
                if (!inCycle[to]) continue;
                if (to == prev) continue;
                nxt = to;
                break;
            }
            prev = cur;
            cur = nxt;
        }
        // cyc now includes start at beginning, and returned to start but not pushed at end
    }

    // position in cycle
    vector<int> posInCycle(n+1, -1);
    for (int i = 0; i < k; i++) posInCycle[cyc[i]] = i;

    auto cyc_next = [&](int v)->int { // cw next in our cyc order
        int p = posInCycle[v];
        return cyc[(p + 1) % k];
    };
    auto cyc_prev = [&](int v)->int { // ccw next
        int p = posInCycle[v];
        return cyc[(p - 1 + k) % k];
    };

    // 3) Build rooted forest (cycle nodes are roots), compute parent/depth/root
    vector<int> parent(n+1, 0), depth(n+1, 0), root(n+1, 0);
    vector<int> order;
    order.reserve(n);

    // stack DFS from each cycle node into its attached tree
    vector<int> stv;
    stv.reserve(n);

    for (int r : cyc) {
        root[r] = r;
        parent[r] = 0;
        depth[r] = 0;
        stv.push_back(r);
        while (!stv.empty()) {
            int v = stv.back(); stv.pop_back();
            order.push_back(v);
            for (int to : g[v]) {
                // do not traverse cycle edges between cycle nodes
                if (inCycle[v] && inCycle[to]) continue;
                if (to == parent[v]) continue;
                if (inCycle[to]) continue; // only go into tree nodes from cycle root
                parent[to] = v;
                depth[to] = depth[v] + 1;
                root[to] = root[v];
                stv.push_back(to);
            }
        }
    }

    // 4) HLD over the forest (on nodes, but storing edge value at node position)
    vector<int> sz(n+1, 0), heavy(n+1, -1);
    // compute subtree sizes in reverse order
    for (int i = (int)order.size() - 1; i >= 0; i--) {
        int v = order[i];
        sz[v] = 1;
        int bestChild = -1, bestSz = 0;
        for (int to : g[v]) {
            if (inCycle[v] && inCycle[to]) continue;
            if (to == parent[v]) continue;
            if (parent[to] != v) continue;
            sz[v] += sz[to];
            if (sz[to] > bestSz) {
                bestSz = sz[to];
                bestChild = to;
            }
        }
        heavy[v] = bestChild;
    }

    vector<int> head(n+1, 0), tin(n+1, 0);
    int timer = 0;

    // Decompose each rooted tree
    for (int r : cyc) {
        int v = r;
        // iterative: push light children as separate chains
        vector<pair<int,int>> stackChains;
        stackChains.push_back({r, r}); // (start node, head)
        while (!stackChains.empty()) {
            auto [x, h] = stackChains.back();
            stackChains.pop_back();
            int curv = x;
            int curHead = h;
            while (curv != -1) {
                head[curv] = curHead;
                tin[curv] = timer++;
                // push light children
                for (int to : g[curv]) {
                    if (inCycle[curv] && inCycle[to]) continue;
                    if (to == parent[curv]) continue;
                    if (parent[to] != curv) continue;
                    if (to == heavy[curv]) continue;
                    stackChains.push_back({to, to});
                }
                curv = heavy[curv];
            }
        }
    }

    // Segment tree for forest edges (size n positions). Value at node v means edge (parent[v], v).
    SegTreeFlip segForest(n);

    auto flip_path_edges_same_tree = [&](int u, int v) {
        // flips all edges along path u-v within the forest (same root)
        while (head[u] != head[v]) {
            if (depth[head[u]] < depth[head[v]]) swap(u, v);
            int hu = head[u];
            segForest.flip(tin[hu], tin[u]); // edges on these nodes include hu..u, excluding parent(hu) edge handled by position of hu itself; ok
            u = parent[hu];
        }
        if (depth[u] < depth[v]) swap(u, v);
        // now v is LCA
        // flip edges from child of v down to u => positions (tin[v]+1 .. tin[u]) in Euler order only works if contiguous, but in HLD final segment is contiguous on chain.
        // Here u and v are in same head; nodes on chain from v to u are contiguous.
        if (u != v) segForest.flip(tin[v] + 1, tin[u]);
    };

    auto flip_up_to_root = [&](int x, int r) {
        // r must be ancestor of x in forest
        while (head[x] != head[r]) {
            int hx = head[x];
            segForest.flip(tin[hx], tin[x]);
            x = parent[hx];
        }
        // same head now
        if (x != r) segForest.flip(tin[r] + 1, tin[x]);
    };

    // Segment tree for cycle edges: edge i corresponds to (cyc[i] -- cyc[(i+1)%k])
    SegTreeFlip segCycle(k);

    auto flip_cycle_cw = [&](int a, int b) {
        // flip edges on cw arc from a to b (excluding b), length cwLen
        int pa = posInCycle[a], pb = posInCycle[b];
        int cwLen = (pb - pa + k) % k;
        if (cwLen == 0) return;
        int l = pa;
        int r = (pa + cwLen - 1) % k;
        if (l <= r) segCycle.flip(l, r);
        else {
            segCycle.flip(l, k-1);
            segCycle.flip(0, r);
        }
    };

    auto choose_cycle_direction = [&](int startCycle, int endCycle) -> bool {
        // returns true if choose cw, false if choose ccw
        int pa = posInCycle[startCycle], pb = posInCycle[endCycle];
        int cwLen = (pb - pa + k) % k;
        int ccwLen = k - cwLen;
        if (cwLen < ccwLen) return true;
        if (cwLen > ccwLen) return false;
        // tie: compare second vertex on the cycle
        int cwSecond = cyc[(pa + 1) % k];
        int ccwSecond = cyc[(pa - 1 + k) % k];
        return cwSecond < ccwSecond;
    };

    auto flip_query_path = [&](int v, int u) {
        int rv = root[v];
        int ru = root[u];
        if (rv == ru) {
            // path entirely in same tree (could be cycle node too)
            flip_path_edges_same_tree(v, u);
            return;
        }
        // flip v up to its cycle root, u up to its cycle root
        flip_up_to_root(v, rv);
        flip_up_to_root(u, ru);

        // flip chosen cycle arc from rv to ru
        bool cw = choose_cycle_direction(rv, ru);
        if (cw) flip_cycle_cw(rv, ru);
        else flip_cycle_cw(ru, rv); // ccw from rv to ru is cw from ru to rv
    };

    //wew dslfi epr sdusrlsc we sdnfwr
    auto comps_cycle = [&](int onesCycle) -> int {
        if (onesCycle == k) return 1;
        return k - onesCycle;
    };

    for (int i = 0; i < m; i++) {
        int v, u;
        cin >> v >> u;
        flip_query_path(v, u);

        int onesTree = segForest.all_sum();
        int onesCycle = segCycle.all_sum();

        int compTrees = n - onesTree;
        int compCycle = comps_cycle(onesCycle);
        int ans = compTrees + compCycle - k;
        cout << ans << "\n";
    }

    return 0;
}
 false; 
            q.pop();
            for (int c : g[f]) {
                deg[c] --;      
                if (deg[c] == 1) {
                    q.push(c); 
                }           
            }
        }
        //w ew hsdy tosh soirhwo rsdk werhw wer
        vector<int> base(n,0);
        vector<int> pos(n,0);            
        for (int i = 0 ; i < n ;i ++) {
            
             
        }


        return ;


    }


