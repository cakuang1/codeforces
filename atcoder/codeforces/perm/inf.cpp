#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while(T--){
        int n;
        cin >> n;
        vi p(n);
        for(int i = 0; i < n; i++){
            cin >> p[i];
            --p[i];
        }
        vi c(n);
        for(int i = 0; i < n; i++){
            cin >> c[i];
        }

        vector<char> vis(n, 0);
        int answer = n;  // upper bound

        vector<int> cycle;
        cycle.reserve(n);

        for(int i = 0; i < n; i++){
            if(vis[i]) continue;
            // extract the cycle starting at i
            cycle.clear();
            int x = i;
            while(!vis[x]){
                vis[x] = 1;
                cycle.push_back(x);
                x = p[x];
            } 
            
            // how does 
            int L = cycle.size();
            // build color list
            vi col(L);
            for(int j = 0; j < L; j++){
                col[j] = c[cycle[j]];
            }
            // find divisors of L
            vector<int> divs;
            for(int d = 1; d * d <= L; d++){
                if(L % d == 0){
                    divs.push_back(d);
                    if(d * d != L) divs.push_back(L / d);
                }
            }
            sort(divs.begin(), divs.end());
            // test each divisor as stride
            for(int d: divs){
                if(d >= answer) break;  // no need to check larger strides
                // check if any residue class mod d is monochromatic
                bool ok = false;
                for(int s = 0; s < d; s++){
                    int v = col[s];
                    bool good = true;
                    for(int k = s; k < L; k += d){
                        if(col[k] != v){
                            good = false;
                            break;
                        }
                    }
                    if(good){
                        ok = true;
                        break;
                    }
                }
                if(ok){
                    answer = d;
                    break;  // no need larger d for this cycle
                }
            }
        }

        cout << answer << "\n";
    }
    return 0;
}
