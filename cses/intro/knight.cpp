#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    // Four by three knight moves:
    static const int dx[8] = {+2,+2,-2,-2,+1,-1,+1,-1};
    static const int dy[8] = {+1,-1,+1,-1,+2,+2,-2,-2};

    // dist[i][j] = min moves from (i,j) to (0,0)
    vector<vector<int>> dist(n, vector<int>(n, -1));
    deque<pair<int,int>> q;

    // start from target (0,0)
    dist[0][0] = 0;
    q.emplace_back(0,0);

    while(!q.empty()){
        auto [x,y] = q.front();
        q.pop_front();
        int d = dist[x][y];
        for(int k=0;k<8;k++){
            int nx = x + dx[k], ny = y + dy[k];
            if(nx>=0 && nx<n && ny>=0 && ny<n && dist[nx][ny]==-1){
                dist[nx][ny] = d+1;
                q.emplace_back(nx,ny);
            }
        }
    }

    // output
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout << dist[i][j] << (j+1<n ? ' ' : '\n');
        }
    }
    return 0;
}

