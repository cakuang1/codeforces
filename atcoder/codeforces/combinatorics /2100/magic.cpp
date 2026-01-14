#include <iostream>
#include <iomanip>
using namespace std;
 
int main(){
    int n, m;
    cin >> n >> m;
    
    // Special case: if n*m == 1 then n==1 and m==1, so the working deck always has the one card.
    if(n * m == 1){
        cout << fixed << setprecision(6) << 1.0 << endl;
        return 0;
    }
    
    // Use long double for precision.
    long double numerator = (n - 1.0L) * (m - 1.0L);
    long double denominator = m * n - 1.0L;
    long double probability = (1.0L / n) * (1.0L + numerator / denominator);
    
    cout << fixed << setprecision(6) << (long double) probability << endl;
    return 0;
}
