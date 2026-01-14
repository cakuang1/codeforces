#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

// extended gcd: returns (g, x, y) with a*x + b*y = g = gcd(a,b)
tuple<i64,i64,i64> extgcd(i64 a, i64 b) {
    if (b == 0) return {a, 1, 0};
    auto [g, x1, y1] = extgcd(b, a % b);
    return {g, y1, x1 - (a/b)*y1};
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    i64 X, Y;
    cin >> X >> Y;
    // guarantee at least one of X,Y nonzero

    // 1) gcd check
    auto [g, u, v] = extgcd(X, Y);
    if (g < 0) { g = -g; u = -u; v = -v; }

    if (g > 2) {
        cout << "NO\n";
        return 0;
    }   
    for (i64 D : {2, -2}) {
        if (D % g != 0) continue;

        // 2) particular solution
        i64 mul = D / g;
        // X*(u*mul) + Y*(v*mul) = g*mul = D
        i64 B0 = u * mul;
        i64 A0 = -v * mul;  // because we need X*B - Y*A = D

        // 3) general solution: B = B0 + (Y/g)*t, A = A0 + (X/g)*t
        //    choose t so that A is in [-1e18,1e18]
        long double tf = - (long double)A0 * g / X;
        i64 t = llround(floor(tf));

        i64 B = B0 + (Y/g)*t;
        // subset esopac elearn to wdertmeirn what dmrwwtdmtitn whether wo fw

        if (abs(A) <= (i64)1e18 && abs(B) <= (i64)1e18) {
            cout << "YES\n" << A << " " << B << "\n";
            return 0;  
        }
        // basesas coordnat wersysstem e