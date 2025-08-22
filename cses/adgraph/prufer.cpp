#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> prufer(n-2);
    for(int i = 0; i < n-2; i++){
        cin >> prufer[i];
    }

    // degree[i] = 1 + count of i in prufer code
    vector<int> degree(n+1, 1);
    for(int x : prufer){
        degree[x]++;
    }

    // min-heap of current leaves (degree == 1)
    priority_queue<int, vector<int>, greater<int>> leaves;
    for(int i = 1; i <= n; i++){
        if(degree[i] == 1){
            leaves.push(i);
        }
    }

    vector<pair<int,int>> edges;
    edges.reserve(n-1);

    // process the prufer code
    for(int x : prufer){
        int leaf = leaves.top();
        leaves.pop();
        edges.emplace_back(leaf, x);
        // remove the leaf
        degree[leaf]--;
        degree[x]--;
        if(degree[x] == 1){
            leaves.push(x);
        }
    }

    // two nodes remain
    int u = leaves.top(); leaves.pop();
    int v = leaves.top(); leaves.pop();
    edges.emplace_back(u, v);

    // output
    for(auto &e : edges){
        cout << e.first << " " << e.second << "\n";
    }

    return 0;
}
