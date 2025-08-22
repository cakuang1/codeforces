#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<pair<int,int>> edges(m);
    for(int i = 0; i < m; i++){
        cin >> edges[i].first >> edges[i].second;
    }
    for(auto &e : edges){
        int a = e.first, b = e.second;
        if(a < b) 
            cout << a << " " << b << "\n";
        else 
            cout << b << " " << a << "\n";
    }
    return 0;
}
