#include <bits/stdc++.h>
using namespace std;

struct Dinic {
    struct Edge { int to, rev; double cap; };
    int n, s, t;
    vector<vector<Edge>> g;
    vector<int> level, it;
    static constexpr double EPS = 1e-9;

    Dinic(int n=0): n(n), s(-1), t(-1), g(n), level(n), it(n) {}
    void reset(int N){ n=N; g.assign(n,{}); level.assign(n,0); it.assign(n,0); }

    void addEdge(int u,int v,double c){
        Edge a{v,(int)g[v].size(),c};
        Edge b{u,(int)g[u].size(),0.0};
        g[u].push_back(a); g[v].push_back(b);
    }

    bool bfs(){
        fill(level.begin(), level.end(), -1);
        queue<int> q; q.push(s); level[s]=0;
        while(!q.empty()){
            int v=q.front(); q.pop();
            for(auto &e:g[v]) if(e.cap>EPS && level[e.to]==-1){
                level[e.to]=level[v]+1; q.push(e.to);
            }
        }
        return level[t]!=-1;
    }

    double dfs(int v,double f){
        if(v==t) return f;
        for(int &i=it[v]; i<(int)g[v].size(); ++i){
            Edge &e=g[v][i];
            if(e.cap>EPS && level[e.to]==level[v]+1){
                double pushed=dfs(e.to,min(f,e.cap));
                if(pushed>EPS){
                    e.cap-=pushed;
                    g[e.to][e.rev].cap+=pushed;
                    return pushed;
                }
            }
        }
        return 0.0;
    }

    double flow(int S,int T){
        s=S; t=T;
        double res=0.0;
        while(bfs()){
            fill(it.begin(),it.end(),0);
            while(true){
                double pushed=dfs(s,1e100);
                if(pushed<=EPS) break;
                res+=pushed;
            }
        }
        return res;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; 
    if(!(cin>>T)) return 0;
    cout.setf(std::ios::fixed); 
    cout<<setprecision(12);

    for(int tc=1; tc<=T; ++tc){
        int n; cin>>n;
        vector<int> p(n);
        for(int i=0;i<n;++i) cin>>p[i];

        vector<pair<int,int>> inv;
        for(int i=0;i<n;++i)
            for(int j=i+1;j<n;++j)
                if(p[i]>p[j]) inv.emplace_back(i,j);
        int M=(int)inv.size();
        if(M==0){
            cout<<"Case #"<<tc<<": "<<0.0<<"\n";
            continue;
        }

        double lo=0.0, hi=n/2.0;
        auto feasible=[&](double g)->bool{
            int Ebase=0, Vbase=M, S=M+n, TT=S+1;
            Dinic din(TT+1);
            const double INF=1e12;

            for(int e=0;e<M;++e) din.addEdge(S,Ebase+e,1.0);
            for(int v=0;v<n;++v) din.addEdge(Vbase+v,TT,g);
            for(int e=0;e<M;++e){
                int u=inv[e].first, v=inv[e].second;
                din.addEdge(Ebase+e,Vbase+u,INF);
                din.addEdge(Ebase+e,Vbase+v,INF);
            }
            double f=din.flow(S,TT);
            return (M - f) > 1e-9;
        };

        for(int it=0; it<60; ++it){
            double mid=0.5*(lo+hi);
            if(feasible(mid)) lo=mid; else hi=mid;
        }
        cout<<"Case #"<<tc<<": "<<lo<<"\n";
    }
    return 0;
}


// wflwwrcotnianstw r/// w
// w