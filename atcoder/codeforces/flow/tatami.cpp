#include <bits/stdc++.h>
#include <atcoder/maxflow>
using namespace std;
using namespace atcoder;

int main() {
    int H, W;
    cin >> H >> W;
    vector<string> b(H);
    for (int i = 0; i < H; i++) cin >> b[i];

    int n = H * W;
    int S = n, T = n + 1;       // normal source/sink
    int Sprime = n + 2, Tprime = n + 3;
    mf_graph<int> g(n + 4);
    vector<int> bal(n + 4, 0);  // node balance
    auto id = [&](int i, int j){ return i * W + j; };
    
    for (int i = 0; i < H; i++) for (int j = 0; j < W; j++) {
        if (b[i][j] == '1') continue;
        int v = id(i,j);
        bool left = ((i + j) % 2 == 0);

        if (left) {
            int L = (b[i][j] == '2' ? 1 : 0);
            int R = 1;
            g.add_edge(S, v, R - L);
            bal[S] -= L; bal[v] += L;
        } else {
            int L = (b[i][j] == '2' ? 1 : 0);
            int R = 1;
            g.add_edge(v, T, R - L);
            bal[v] -= L; bal[T] += L;
        }

        // demtienr the balacne w

        // w
        const int di[4]={1,-1,0,0}, dj[4]={0,0,1,-1};
        for(int d=0; d<4; d++){
            int ni=i+di[d], nj=j+dj[d];
            if(ni<0||nj<0||ni>=H||nj>=W) continue;
            if(b[ni][nj]=='1') continue;
            int u = id(ni,nj);
            if(left) g.add_edge(v,u,1);
        }
    }
    
    for(int v=0; v<n+4; v++){
        if(bal[v] > 0) g.add_edge(Sprime, v, bal[v]);
        else if(bal[v] < 0) g.add_edge(v, Tprime, -bal[v]);
    }
    // do shtiwwor kwer
    g.add_edge(T, S, 1e9);

    // Run single max flow
    int totalPos = 0;
    for(int x: bal) if(x>0) totalPos += x;
    int flow = g.flow(Sprime, Tprime);

    if(flow == totalPos) cout << "Yes\n";
    else cout << "No\n";
}


// dosehti wrwor kwrw a werhw ywer we