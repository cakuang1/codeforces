#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<string> grid(n);
    for(int i = 0; i < n; i++)
        cin >> grid[i];

    string ans;
    ans.reserve(2*n - 1);
    ans.push_back(grid[0][0]);

    vector<pair<int,int>> curr, next;
    curr.reserve(n);
    next.reserve(n);
    curr.emplace_back(0, 0);

    vector<char> seen(n);
    for(int s = 1; s <= 2*n - 2; s++){
        // 1) find the smallest letter on the next anti-diagonal
        char best = 'Z';
        for(auto [i,j] : curr){
            if(i+1 < n) best = min(best, grid[i+1][j]);
            if(j+1 < n) best = min(best, grid[i][j+1]);
        }
        ans.push_back(best);

        // 2) build the next frontier of only those cells with grid == best
        fill(seen.begin(), seen.end(), 0);
        next.clear();
        for(auto [i,j] : curr){
            if(i+1 < n && grid[i+1][j] == best && !seen[i+1]){
                seen[i+1] = 1;
                next.emplace_back(i+1, j);
            }
            if(j+1 < n && grid[i][j+1] == best && !seen[i]){
                seen[i] = 1;
                next.emplace_back(i, j+1);
            }
        }

        curr.swap(next);
    }

    cout << ans << "\n";
    return 0;
}
