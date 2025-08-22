#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<double> A(n+1), B(n+1);
    for(int i = 1; i <= n; i++){
        cin >> A[i];
        A[i] += A[i-1];
    }
    for(int j = 1; j <= n; j++){
        cin >> B[j];
        B[j] += B[j-1];
    }

    // Check if average X is feasible: is there i,j >=1 
    // with (A[i]-X*i)+(B[j]-X*j) >= 0 ?
    auto feasible = [&](double X){
        double bestA = -1e300;
        for(int i = 1; i <= n; i++){
            bestA = max(bestA, A[i] - X*i);
        }
        double bestB = -1e300;
        for(int j = 1; j <= n; j++){
            bestB = max(bestB, B[j] - X*j);
        }
        return (bestA + bestB >= 0.0);
    };

    // Binary‐search the maximum average in [0..1e9]
    double lo = 0, hi = 1e9;
    for(int it = 0; it < 60; it++){
        double mid = (lo + hi) / 2;
        if(feasible(mid)) lo = mid;
        else             hi = mid;
    }
    double X = lo;

    // Now recover the actual i,j that realize it
    double bestA = -1e300; int bi = 1;
    for(int i = 1; i <= n; i++){
        double v = A[i] - X*i;
        if(v > bestA){
            bestA = v;
            bi = i;
        }
    }
    double bestB = -1e300; int bj = 1;
    for(int j = 1; j <= n; j++){
        double v = B[j] - X*j;
        if(v > bestB){
            bestB = v;
            bj = j;
        }
    }

    // bi, bj are the prefix‐lengths.
    cout << bi << " " << bj << "\n";
    return 0;
}
// 
// zero sum wsubset  w

 

// ww 