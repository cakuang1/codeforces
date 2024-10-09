 #include <iostream>
 #include <string>
using namespace std;
int main() {
    int m,n;
    cin >> m >> n; 
    int res = (n/2) * m;

    if (n % 2 == 1) {
        res += m/2;
    }     
    cout  << res << endl;    
    return 0;
}


// domino piling  