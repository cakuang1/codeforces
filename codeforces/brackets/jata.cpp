#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n; 
        string s;
        cin >> s;
    
        int res = 0;
        
        vector<int> stack; 
        for (int i = 0 ; i < 2 * n ; i ++ ) {
            if (s[i] == '(') { 
                stack.push_back(i); 
            } else {
                
            }            
        }

        
        // detemrin rall wernestwed wew



        cout << res << endl;
        
    }

    return 0;
}


// run nessetedwedpeth  wer