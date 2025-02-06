#include <bits/stdc++.h>
using namespace std;
int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);    
    int  n ; cin >> n; 
    vector<int> arr(n); 
    for (int i = 0 ; i  <n; i ++) {
        cin >> arr[i];
    }
    map<int,int> latest; 
    vector<int> prev(n , -1);
    vector<int> next(n , -1);
    for (int i = 0 ; i < n; i ++) {
        int val =  arr[i]; 
        if (latest.find(val) != latest.end()) {
            prev[i] = latest[val];
            next[latest[val]] = i;  
            latest[val] = i; 
        } 
    }

    int ans = 0 ;
    for (int i = 0 ; i < n ; i++) {        
        int leftmul,rightmul;
        if (prev[i] == -1) {
            leftmul = i + 1;
        } else{
            leftmul = i - prev[i];  
        }
        if (next[i] == -1) {
            rightmul = (n - i); 
        } else{
            rightmul =  next[i] - i;
        }
        ans += (leftmul * rightmul);   
    }
    cout << ans << endl;
    
    

  	return 0;
}
 

