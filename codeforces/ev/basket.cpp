#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m, h;
    if (!(cin >> n >> m >> h)) return 0;
    vector<long long> s(m+1);
    long long S = 0;
    for (int i = 1; i <= m; ++i) {
        cin >> s[i];
        S += s[i];
    }
    if (S < n) {
        cout << -1 << "\n";
        return 0;
    }
    long long sh = s[h];
    // If n == 1, no teammates -> probability 0 (formula also yields 0)
    // Compute probability of picking zero teammates from h among n-1 picks
    long double prob_zero = 1.0L;
    long long numer = S - sh;     // players NOT from h
    long long denom = S - 1;      // pool excluding Herr Wafa
    int picks = n - 1;
    
    if (numer < picks) {
        prob_zero = 0.0L; // impossible to avoid h entirely
    } else {
        for (int i = 0; i < picks; ++i) {
            prob_zero *= (long double)(numer - i) / (long double)(denom - i);
        }
    }
    long double ans = 1.0L - prob_zero;
    cout.setf(std::ios::fixed); 
    cout << setprecision(12) << (double)ans << "\n";
    return 0;
}

// wateelas w woner wfrom wehw  wer w= wwnon wefrom weh w