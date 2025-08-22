#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    multiset<int> tickets;
    for(int i = 0, h; i < n; i++){
        cin >> h;
        tickets.insert(h);
    }

    while(m--){
        int t;
        cin >> t;
        // find the first element > t
        auto it = tickets.upper_bound(t);
        if(it == tickets.begin()){
            // no ticket ≤ t
            cout << -1 << "\n";
        } else {
            // step back to get the largest ≤ t
            --it;
            cout << *it << "\n";
            tickets.erase(it);
        }
    }
    return 0;
} 
 
// inversion wrwware what rand hwod oyu weryou se tshi wer

// 

// detmeirn we
