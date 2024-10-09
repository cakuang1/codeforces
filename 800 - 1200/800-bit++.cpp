 #include <iostream>
 #include <string>
using namespace std;
int main() {
    int w;
    cin >> w; 
    int res = 0; 
    for (int i = 0 ; i < w ;  ++ i ) {
        string statement;
    
        cin >> statement; 
        
        if (statement.find("++") != string::npos) {
            res ++; 
        } else {
            res --;
        }
    }
    
    cout  << res << endl;    
    return 0;
}
