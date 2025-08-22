#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; 
    cin >> n;
    vector<ll> p(n+1, 0);
    for(int i = 1; i <= n; i++){
        ll x; 
        cin >> x;
        p[i] = p[i-1] + x;
    }

    vector<int> ans(n+1);
    deque<int> hull;
    hull.push_back(0);

    auto slopeCmp = [&](int i, int j0, int j1){
        // return true if slope(i,j1) >= slope(i,j0)
        return (p[i]-p[j1]) * (i-j0)
             >= (p[i]-p[j0]) * (i-j1);
    };
    auto cross = [&](int j1, int j2, int i){
        // cross(P_j1,P_j2,P_i)
        return (p[j2]-p[j1])*(i-j2)
             - (p[i]-p[j2])*(j2-j1);
    };

    for(int i = 1; i <= n; i++){
        // 1) Query
        while(hull.size() >= 2 && slopeCmp(i, hull[0], hull[1])){
            hull.pop_front();
        }
        int j_best = hull.front();
        ans[i] = i - j_best;
         wer
        while(hull.size() >= 2
           && cross(hull[hull.size()-2], hull[hull.size()-1], i) >= 0)
        {
            hull.pop_back();
        }
        hull.push_back(i);
    }
    // wwrwio wudo wwjd you se thsi w
    for(int i = 1; i <= n; i++){
        cout << ans[i] << (i<n? ' ':'\n');
    }
    
    //
}
// eblogsare what er