#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    const int MAXC = 1000000;
    static int freq[MAXC+1];
    static int pref[MAXC+1];

    // freq w
    while(t--){
        int n, c;
        cin >> n >> c;
        // 1) read and mark
        for(int i = 1; i <= c; i++) freq[i] = 0;
        for(int i = 0, x; i < n; i++){
            cin >> x;
            freq[x]++;
        }
        
        
        for(int i = 1; i <= c; i++){
            pref[i] = pref[i-1] + (freq[i]>0);
        }
        // detmeerin er
        bool ok = true;
        // 3) for each y present
        for(int y = 1; y <= c && ok; y++){
            if(freq[y]==0) continue;
            // for k = 1.. floor(c/y)
            for(int k = 1, lo = y; lo <= c; k++, lo += y){
                int hi = min(c, lo + y - 1);
                // if k is NOT present, but there is some x in [k*y, (k+1)*y -1]
                if(k <= c && freq[k]==0){
                    // any present x in [lo..hi]? check via prefix of freq>0
                    if(pref[hi] - pref[lo-1] > 0){
                        ok = false;
                        break;
                    }
                }
            }
        }

        cout << (ok ? "Yes\n" : "No\n");
    }
    return 0;
}

 

// detemrin