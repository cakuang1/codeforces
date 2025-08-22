#include <bits/stdc++.h>
using namespace std;
using cd = complex<double>;
const double PI = acos(-1);

// Cooley–Tuk FFT, in-place
void fft(vector<cd>& a, bool invert) {
    int n = a.size();
    // bit‐reverse permutation
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j |= bit;
        if (i < j) swap(a[i], a[j]);
    }
    // butterflies
    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : +1);
        cd wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            cd w(1);
            for (int j = 0; j < len/2; j++) {
                cd u = a[i + j];
                cd v = a[i + j + len/2] * w;
                a[i + j] = u + v;
                a[i + j + len/2] = u - v;
                w *= wlen;
            }
        }
    }
    if (invert) {
        for (cd &x : a) x /= n;
    }
}

vector<long long> convolve(const vector<long long>& A, const vector<long long>& B) {
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
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k, n, m;
    cin >> k >> n >> m;
    vector<long long> freqA(k+1), freqB(k+1);
    for (int i = 0, x; i < n; i++){
        cin >> x;
        freqA[x]++;
    }
    for (int i = 0, x; i < m; i++){
        cin >> x;
        freqB[x]++;
    }
    // convolve freqA and freqB
    auto C = convolve(freqA, freqB);
    // C[w] = sum_{i+j=w} freqA[i]*freqB[j]
    // we need w=2..2k
    for (int w = 2; w <= 2*k; w++) {
        long long ans = (w < (int)C.size() ? C[w] : 0);
        cout << ans << (w<2*k ? ' ' : '\n');
    }
    return 0;
}
