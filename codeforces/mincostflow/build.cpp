#include <bits/stdc++.h>
using namespace std;

struct MCMF {
    struct Edge { int to, rev, cap; long long cost; };
    int n;
    vector<vector<Edge> > g;
    vector<long long> dist, pot;
    vector<int> pv, pe;

    MCMF(int n) : n(n), g(n), dist(n), pot(n), pv(n), pe(n) {}

    void add_edge(int u, int v, int cap, long long cost) {
        Edge a = {v, (int)g[v].size(), cap, cost};
        Edge b = {u, (int)g[u].size(), 0, -cost};
        g[u].push_back(a);
        g[v].push_back(b);
    }

    pair<long long,long long> min_cost_max_flow(int s, int t, int maxf) {
        long long flow = 0, cost = 0;
        fill(pot.begin(), pot.end(), 0);
        while (flow < maxf) {
            fill(dist.begin(), dist.end(), LLONG_MAX);
            dist[s] = 0;
            typedef pair<long long,int> pli;
            priority_queue<pli, vector<pli>, greater<pli> > pq;
            pq.push(make_pair(0, s));
            while (!pq.empty()) {
                pli cur = pq.top(); pq.pop();
                long long d = cur.first; int v = cur.second;
                if (d != dist[v]) continue;
                for (int i = 0; i < (int)g[v].size(); ++i) {
                    Edge &e = g[v][i];
                    if (e.cap <= 0) continue;
                    long long nd = d + e.cost + pot[v] - pot[e.to];
                    if (nd < dist[e.to]) {
                        dist[e.to] = nd;
                        pv[e.to] = v;
                        pe[e.to] = i;
                        pq.push(make_pair(nd, e.to));
                    }
                }
            }
            if (dist[t] == LLONG_MAX) break;
            for (int i = 0; i < n; ++i)
                if (dist[i] < LLONG_MAX)
                    pot[i] += dist[i];

            int addf = maxf - flow;
            for (int v = t; v != s; v = pv[v])
                addf = min(addf, g[pv[v]][pe[v]].cap);
            flow += addf;
            cost += 1LL * addf * pot[t];
            for (int v = t; v != s; v = pv[v]) {
                Edge &e = g[pv[v]][pe[v]];
                e.cap -= addf;
                g[v][e.rev].cap += addf;
            }
        }
        return make_pair(flow, cost);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string t;
    cin >> t;
    int n;
    cin >> n;
    vector<string> s(n);
    vector<int> a(n);
    for (int i = 0; i < n; ++i)
        cin >> s[i] >> a[i];

    vector<int> need(26, 0);
    for (char ch : t) need[ch - 'a']++;

    int letters = 26;
    int S = letters + n;
    int T = S + 1;
    MCMF mcmf(T + 1);

    // S -> char
    for (int c = 0; c < 26; ++c)
        if (need[c] > 0)
            mcmf.add_edge(S, c, need[c], 0);

    // char -> string
    for (int i = 0; i < n; ++i) {
        vector<int> cnt(26, 0);
        for (char ch : s[i]) cnt[ch - 'a']++;
        for (int c = 0; c < 26; ++c)
            if (cnt[c] > 0)
                mcmf.add_edge(c, letters + i, cnt[c], i + 1); // cost = i+1 rubles
        mcmf.add_edge(letters + i, T, a[i], 0);
    }

    int total_need = (int)t.size();
    pair<long long,long long> res = mcmf.min_cost_max_flow(S, T, total_need);
    if (res.first < total_need) cout << -1 << "\n";
    else cout << res.second << "\n";
    return 0;
}


// wehat do we need we

// push  wx charcertesr 
// cost rfo tshis wersi what we w

// minium rubles needed wer
// w