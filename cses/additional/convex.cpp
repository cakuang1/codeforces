#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128_t;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<i64> x(n+1), S(n+1,0);
    for(int i = 1; i <= n; i++){
        cin >> x[i];
        S[i] = S[i-1] + x[i];
    }

    // hull of candidate j's
    deque<int> hull;
    hull.push_back(0);  // j=0 is always a candidate

    vector<int> answer(n+1);
    for(int i = 1; i <= n; i++){
        // 1) Query: pop front while next gives >= slope
        while(hull.size() >= 2){
            int j1 = hull[0], j2 = hull[1];
            // if slope(j1,i) <= slope(j2,i), discard j1
            i128 lhs = i128(S[i] - S[j1]) * (i - j2);
            i128 rhs = i128(S[i] - S[j2]) * (i - j1);
            if(lhs <= rhs) hull.pop_front();
            else break;
        }
        int best_j = hull.front();
        // longest = i - best_j
        answer[i] = i - best_j;

    // 1) Query: pop front while next gives strictly better slope
    while (hull.size() >= 2) {
        int j1 = hull[0], j2 = hull[1];
        // want slope(j1,i) < slope(j2,i) to pop j1
        i128 lhs = i128(S[i] - S[j1]) * (i - j2);
        i128 rhs = i128(S[i] - S[j2]) * (i - j1);
        if (lhs < rhs) hull.pop_front();
        else           break;
    }
        hull.push_back(i);
    }
    
    for(int i = 1; i <= n; i++){
        cout << answer[i] << " ";
    }
    cout << "\n";
    return 0;
} 
// werdoesgt wewor kwe e
