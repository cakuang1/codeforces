#include <bits/stdc++.h>
using namespace std;

static const int INF = 1e9;
int n, m;
bool adj_same[1001][1001];      // adj_same[u][v] = true if there is an edge u–v
bool vis[1001][1001];           // vis[a][b] = true once (a,b) has been enqueued
vector<int> G[1001][26];        // G[u][c] = list of neighbors v of u via character 'a'+c

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for(int i = 0; i < m; i++){
        int u, v; char ch;
        cin >> u >> v >> ch;
        int c = ch - 'a';
        G[u][c].push_back(v);
        G[v][c].push_back(u);
        adj_same[u][v] = adj_same[v][u] = true;
    }

    int answer = INF;
    queue<tuple<int,int,int>> q;
    q.emplace(1, n, 0);
    vis[1][n] = true;

    while(!q.empty()){
        auto [x, y, d] = q.front();
        q.pop();
        if(d > answer) break;

        // even-length meet: same vertex
        if(x == y)
            answer = min(answer, d);

        // odd-length meet: adjacent vertices
        if(adj_same[x][y])
            answer = min(answer, d + 1);

        // try to advance both ends along the same character
        for(int c = 0; c < 26; c++){
            for(int nx : G[x][c]){
                for(int ny : G[y][c]){
                    if(!vis[nx][ny]){
                        vis[nx][ny] = true;
                        // two steps (one at each end)
                        q.emplace(nx, ny, d + 2);
                    }
                }
            }
        }
    }
        
    if(answer == INF) answer = -1;
    cout << answer << "\n";
    return 0;
}
