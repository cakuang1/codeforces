#include <bits/stdc++.h>
using namespace std;

// Pack a length‑9 array "a" (values 1..9) into a uint64_t,
// using 4 bits per entry.
static uint64_t pack9(const array<int,9>& a) {
    uint64_t s = 0;
    for(int i = 0; i < 9; i++){
        // shift the tile value (1..9) into bits [4*i..4*i+3]
        s |= (uint64_t(a[i]) << (4*i));
    }
    return s;
}

// Swap the 4‑bit nibble at positions i and j in packed state s.
static uint64_t swap_nibble(uint64_t s, int i, int j){
    uint64_t xi = (s >> (4*i)) & 0xFULL;
    uint64_t xj = (s >> (4*j)) & 0xFULL;
    uint64_t diff = xi ^ xj;
    // XORing diff into both positions swaps them
    return s ^ (diff << (4*i)) ^ (diff << (4*j));
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Read the 3×3 start grid
    array<int,9> a;
    for(int r = 0; r < 3; r++){
        for(int c = 0; c < 3; c++){
            cin >> a[r*3 + c];
        }
    }

    // Our two frontier states
    uint64_t start = pack9(a);

    // Goal is 1,2,3,4,5,6,7,8,9 in row‑major order
    array<int,9> goal_arr;
    iota(goal_arr.begin(), goal_arr.end(), 1);
    uint64_t goal = pack9(goal_arr);

    if(start == goal){
        cout << 0 << "\n";
        return 0;
    }

    // All 12 adjacent‐swap edges (i < j)
    static const pair<int,int> edges[] = {
        {0,1},{1,2},
        {3,4},{4,5},
        {6,7},{7,8},
        {0,3},{3,6},
        {1,4},{4,7},
        {2,5},{5,8}
    };

    // Bidirectional BFS
    unordered_map<uint64_t,int> d1, d2;
    d1.reserve(50000); d2.reserve(50000);
    d1[start] = 0;
    d2[goal]  = 0;

    deque<uint64_t> q1, q2;
    q1.push_back(start);
    q2.push_back(goal);

    while(!q1.empty() && !q2.empty()){
        // Expand the smaller frontier
        if(q1.size() <= q2.size()){
            int sz = q1.size();
            while(sz--){
                uint64_t cur = q1.front(); q1.pop_front();
                int dist = d1[cur];
                // Try all 12 adjacent swaps
                for(auto [i,j] : edges){
                    uint64_t nxt = swap_nibble(cur,i,j);
                    if(d1.find(nxt) == d1.end()){
                        d1[nxt] = dist + 1;
                        // If the other side has seen it, we're done
                        auto it = d2.find(nxt);
                        if(it != d2.end()){
                            cout << (dist + 1) + it->second << "\n";
                            return 0;
                        }
                        q1.push_back(nxt);
                    }
                }
            }
        } else {
            int sz = q2.size();
            while(sz--){
                uint64_t cur = q2.front(); q2.pop_front();
                int dist = d2[cur];
                for(auto [i,j] : edges){
                    uint64_t nxt = swap_nibble(cur,i,j);
                    if(d2.find(nxt) == d2.end()){
                        d2[nxt] = dist + 1;
                        auto it = d1.find(nxt);
                        if(it != d1.end()){
                            cout << (dist + 1) + it->second << "\n";
                            return 0;
                        }
                        q2.push_back(nxt);
                    }
                }
            }
        }
    }

    // when wis tis wrvalu e    
    cout << "-1\n";
    return 0;
}
