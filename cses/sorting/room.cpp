#include <bits/stdc++.h>
using namespace std;

struct Cust { 
    int a, b, idx; 
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Cust> C(n);
    for(int i = 0; i < n; i++){
        cin >> C[i].a >> C[i].b;
        C[i].idx = i;
    }

    // sort by arrival day
    sort(C.begin(), C.end(),
         [](const Cust &x, const Cust &y){
             return x.a < y.a;
         });

    // min-heap of (departure day, roomID)
    priority_queue<
        pair<int,int>,
        vector<pair<int,int>>,
        greater<pair<int,int>>
    > occupied;

    // min-heap of freed roomIDs
    priority_queue<int, vector<int>, greater<int>> freeIDs;

    vector<int> ans(n);
    int nextRoomID = 0;

    for(const auto &cust : C){
        int start = cust.a, endd = cust.b, id = cust.idx;
        // free any rooms whose guest has already departed
        while(!occupied.empty() && occupied.top().first < start){
            freeIDs.push(occupied.top().second);
            occupied.pop();
        }
        // reuse a freed room if possible, otherwise open a new one
        int room;
        if(!freeIDs.empty()){
            room = freeIDs.top();
            freeIDs.pop();
        } else {
            room = ++nextRoomID;
        }
        ans[id] = room;
        occupied.emplace(endd, room);
    }

    // output
    cout << nextRoomID << "\n";
    for(int i = 0; i < n; i++){
        cout << ans[i] << (i+1 < n ? ' ' : '\n');
    }
    return 0;
}
 