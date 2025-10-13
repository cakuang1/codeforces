#include <bits/stdc++.h>
using namespace std;

struct MCMF {
    struct Edge { int v, cap, cost, rev; };
    int N;
    vector<vector<Edge>> G;
    MCMF(int n=0): N(n), G(n) {}
    void addEdge(int u, int v, int cap, int cost){
        Edge a{v,cap,cost,(int)G[v].size()};
        Edge b{u,0,-cost,(int)G[u].size()};
        G[u].push_back(a); G[v].push_back(b);
    }
    pair<int,long long> minCostMaxFlow(int s, int t, int maxf=INT_MAX){
        const long long INF = (1LL<<60);
        long long cost = 0;
        int flow = 0;
        vector<long long> dist(N), pot(N);
        vector<int> pv(N), pe(N);
        // SPFA init potentials
        vector<int> inq(N,0); queue<int>q;
        fill(dist.begin(), dist.end(), INF);
        dist[s]=0; q.push(s); inq[s]=1;
        while(!q.empty()){
            int u=q.front(); q.pop(); inq[u]=0;
            for(int i=0;i<(int)G[u].size();++i){
                auto &e=G[u][i];
                if(e.cap>0 && dist[e.v]>dist[u]+e.cost){
                    dist[e.v]=dist[u]+e.cost;
                    if(!inq[e.v]){inq[e.v]=1; q.push(e.v);}
                }
            }
        }
        for(int i=0;i<N;++i) pot[i]=(dist[i]>=INF?0:dist[i]);
        while(flow<maxf){
            fill(dist.begin(), dist.end(), INF);
            vector<char> vis(N,0);
            dist[s]=0;
            priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> pq;
            pq.push({0,s});
            while(!pq.empty()){
                auto [d,u]=pq.top(); pq.pop();
                if(vis[u]) continue; vis[u]=1;
                for(int i=0;i<(int)G[u].size();++i){
                    auto &e=G[u][i];
                    if(e.cap<=0) continue;
                    long long nd = d + e.cost + pot[u] - pot[e.v];
                    if(nd < dist[e.v]){
                        dist[e.v]=nd; pv[e.v]=u; pe[e.v]=i;
                        pq.push({nd,e.v});
                    }
                }
            }
            if(dist[t]==INF) break;
            for(int i=0;i<N;++i) if(dist[i]<INF) pot[i]+=dist[i];
            int aug = maxf - flow;
            for(int v=t; v!=s; v=pv[v])
                aug = min(aug, G[pv[v]][pe[v]].cap);
            for(int v=t; v!=s; v=pv[v]){
                auto &e=G[pv[v]][pe[v]];
                auto &er=G[v][e.rev];
                e.cap-=aug; er.cap+=aug;
            }
            flow += aug;
            cost += 1LL*aug * pot[t];
        }
        return {flow, cost};
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n1,n2,m; long long r,b;
    if(!(cin>>n1>>n2>>m>>r>>b)) return 0;
    string sL,sR; cin>>sL>>sR;
    vector<int> U(m), V(m);
    for(int i=0;i<m;++i){ cin>>U[i]>>V[i]; --U[i]; --V[i]; }

    int L0 = 0;
    int R0 = n1;
    int oldS = n1+n2;
    int oldT = oldS+1;
    int Spr = oldT+1;
    int Tpr = Spr+1;
    int N = Tpr+1;
    MCMF mf(N);

    vector<long long> bal(N,0);
    auto add_with_LB = [&](int u, int v, int L, int C, int cost){
        if(C < L){ cout << -1 << "\n"; exit(0); }
        if(C-L > 0) mf.addEdge(u, v, C-L, cost);
        bal[u] -= L;
        bal[v] += L;
    };

    const int INF = 1e9;
    // Left vertices
    for(int u=0; u<n1; ++u){
        if(sL[u]=='R'){
            add_with_LB(oldS, u, 1, m, 0);
        }else if(sL[u]=='B'){
            add_with_LB(u, oldT, 1, m, 0);
        }else{
            mf.addEdge(oldS, u, m, 0);
            mf.addEdge(u, oldT, m, 0);
        }
    }

    // Right vertices (fixed directions)
    for(int v=0; v<n2; ++v){
        int node = R0+v;
        if(sR[v]=='R'){
            add_with_LB(oldS, node, 1, m, 0); // must receive ≥1
        }else if(sR[v]=='B'){
            add_with_LB(node, oldT, 1, m, 0); // must send ≥1
        }else{
            mf.addEdge(oldS, node, m, 0);
            mf.addEdge(node, oldT, m, 0);
        }
    }

    // Original bidirectional edges
    for(int i=0;i<m;++i){
        int u = U[i];
        int v = R0 + V[i];
        mf.addEdge(u, v, 1, (int)r); // Red
        mf.addEdge(v, u, 1, (int)b); // Blue
    }

    mf.addEdge(oldT, oldS, INF, 0);

    long long need = 0;
    for(int v=0; v<N; ++v){
        if(bal[v] > 0){
            mf.addEdge(Spr, v, (int)bal[v], 0);
            need += bal[v];
        }else if(bal[v] < 0){
            mf.addEdge(v, Tpr, (int)(-bal[v]), 0);
        }
    }

    auto res = mf.minCostMaxFlow(Spr, Tpr);
    if(res.first != need){
        cout << -1 << "\n";
        return 0;
    }

    // Decode colors
    vector<vector<int>> cntLR(n1, vector<int>(n2, 0));
    vector<vector<int>> cntRL(n1, vector<int>(n2, 0));

    for(int u=0; u<n1; ++u){
        for(auto &e : mf.G[u]){
            int v = e.v;
            if(v>=R0 && v<R0+n2){
                auto &rev = mf.G[v][e.rev];
                int flow = rev.cap;
                if(flow>0) cntLR[u][v-R0] += flow;
            }
        }
    }
    for(int vR=0; vR<n2; ++vR){
        int nodeR = R0+vR;
        for(auto &e : mf.G[nodeR]){
            int u = e.v;
            if(u>=0 && u<n1){
                auto &rev = mf.G[u][e.rev];
                int flow = rev.cap;
                if(flow>0) cntRL[u][vR] += flow;
            }
        }
    }

    //
    //w rseuwlet tshi shudl wentwwor wkead nwer wrw w wea wwthw ofoer an wofdw whwer wa anwer r w
    // w we 
    // wcan taek ehte offessranyw edi wa weher a wantwaw
    // vasta acna atkae erofferea an y wroder her wantw e

    // determin wethew wernmaximuwer mwr  vwywwe difsudfsfxuk wetwthw yr? werw
    // we w
    // vasar and endlsesscredit wrbvasya eranwet ofbuthim self anewie new car
    // w unfoarenta el wehe lacks sosme oney ercurrent wlytwerhe has excatly wer buerks wer// whoevwerthe eloa werbane werhas n credit fofers wr
    //wwa rr wethese insideetsanswerwho do yosu oslvsehtis er
    
    // w
    // wcearllyw you rwan wt ot kaewone mont herat  a time w
    // wwan wdowerhe want w eahcwemtoh wrbvata ear
    //we
    // mdi werl wefo som eemornh wrhe takesal tw e wmoey were curenthas and buts the car of that excar pricewer
    //w 
    long long totalCost = 0;
    string paint; paint.reserve(m);
    for(int i=0;i<m;++i){
        int u = U[i], v = V[i];
        if(cntLR[u][v] > 0){
            cntLR[u][v]--;
            totalCost += r;
            paint.push_back('R');
        }else if(cntRL[u][v] > 0){
            cntRL[u][v]--;
            totalCost += b;
            paint.push_back('B');
        }else{
            paint.push_back('U');
        }
    }
    // capitair nweramreicna asay wes rhat wr
    // westesdve reigsers sidfaciaewtwnat wion rd witw hwnew vaian shields erhsielw r
    / w

    cout << totalCost << "\n" << paint << "\n";
    return 0;
}

//d istwwtw twork weand we
