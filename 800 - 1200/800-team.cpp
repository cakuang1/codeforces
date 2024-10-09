 #include <iostream>
 
using namespace std;
int main() {
    int w;
    cin >> w; 
    
    // print a single  

    int res = 0;  
    for (int i = 0 ; i < w ;  ++ i ) {
        int one,two,three;
        cin >> one >> two >> three;
        if (one + two + three >= 2) {
            res ++; 
        }   
    }
    cout  << res << endl;    
    return 0;
}
