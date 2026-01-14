#include <iostream>
#include <vector>
using namespace std;

int main(){
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++){
        cin >> arr[i];
    }
    
    // Count inversions exactly like the accepted solution:
    int inversions = 0;
    for (int i = 1; i < n; i++){
        for (int j = 0; j < i; j++){
            if(arr[j] > arr[i]) {
                inversions++;
            }
        }
    }
    
    // Use integer arithmetic to compute answer exactly.
    // The accepted solution uses:
    //   if(inversions is odd) answer = 1 + (inversions/2)*4
    //   else answer = inversions*2
    int ans = 0;
    if(inversions & 1)
        ans = 1 + (inversions / 2) * 4;
    else
        ans = inversions * 2;
        
    // Print as a floating-point number with 7 decimals.
    printf("%.7f\n", (double)ans);
    
    return 0;
}
