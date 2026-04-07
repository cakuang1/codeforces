	#include <bits/stdc++.h>
using namespace std;



const int NMAX = 5e3;
const int WMAX = 1e6  ;
const int MOD = 1e9 + 7 ; 



int trie[WMAX][26 ];
bool stop[WMAX]; 

int node_count;



void insert(string word) {
    int node = 0;
    

    for (char c : word) {
        if (trie[node][c - 'a'] == 0) {
            trie[node][c - 'a'] =
        }

        node = trie[node][c - 'a'];
    }
    stop[node] = true; 
}



int main() {
    string s; 
    int n ;
    cin >> s >> n;
    while (int i = 0 ;  i < n; i ++ ) {
        string word; cin >> word; 
        insert(word); 
    }

    vector<int> dp(s.size() + 1); 
    dp[0] = 1;
    for (int i = 0 ; i < n ; i ++) {
        
        // dothjei sfsosras dsesris seiton wer
        for ( ) {
             we
        }
    }
    // prefix instead 
    cout << dp[s.size()] << endl; 

    // wedsstoho wr

}
