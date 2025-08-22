#include <bits/stdc++.h>
using namespace std;
using cd = complex<double>;
const double PI = acos(-1);

// Recursive Cooley–Tuk FFT
void fft(vector<cd> & a, bool invert) {
    int n = a.size();
    if (n == 1) return;

    vector<cd> a0(n/2), a1(n/2);
    for (int i = 0; i < n/2; i++) {
        a0[i] = a[2*i];
        a1[i] = a[2*i+1];
    }
    fft(a0, invert);
    fft(a1, invert);

    double ang = 2 * PI / n * (invert ? -1 : +1);
    cd w(1), wn(cos(ang), sin(ang));
    for (int i = 0; i < n/2; i++) {
        cd u = a0[i];
        cd v = w * a1[i];
        a[i]       = u + v;           // butterfly: a+b
        a[i + n/2] = u - v;           // butterfly: a−b
        w *= wn;
    }
}

// Multiply two real-coefficient polynomials via FFT
vector<long long> convolution(const vector<long long>& A, const vector<long long>& B) {
    int n = 1;
    while (n < (int)A.size() + (int)B.size()) 
        n <<= 1;
    vector<cd> fa(n), fb(n);
    for (int i = 0; i < (int)A.size(); i++) fa[i] = A[i];
    for (int i = 0; i < (int)B.size(); i++) fb[i] = B[i];
    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++) 
        fa[i] *= fb[i];
    fft(fa, true);

    vector<long long> C(n);
    for (int i = 0; i < n; i++)
        C[i] = (long long)round(fa[i].real());
    return C;
}

int main(){
    // Example: multiply (1 + 2x + 3x^2) * (4 + 5x)
    vector<long long> P = {1,2,3};
    vector<long long> Q = {4,5};

    auto R = convolution(P, Q);
    // R should represent 1*4 + (1*5+2*4)x + (2*5+3*4)x^2 + (3*5)x^3
    // i.e. [4, 13, 22, 15]

    cout << "Result coefficients:\n";
    for (int i = 0; i < (int)R.size(); i++) {
        // trailing zeros beyond degree deg(P)+deg(Q)
        if (i >= (int)P.size() + (int)Q.size() - 1) break;
        cout << "x^" << i << ": " << R[i] << "\n";
    }
    return 0;
}
