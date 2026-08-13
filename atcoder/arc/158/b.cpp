#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<long double> x(N);
    for (auto &v : x) cin >> v;

    // Sort by 1/x.
    // Equivalent order:
    // negatives descending, then positives descending.
    sort(x.begin(), x.end(), [](long double a, long double b) {
        return 1.0L / a < 1.0L / b;
    });

    vector<long double> cand;

    for (int i = 0; i < min(N, 3); i++) {
        cand.push_back(x[i]);
    }

    for (int i = max(0, N - 3); i < N; i++) {
        cand.push_back(x[i]);
    }

    long double mn = 1e100L;
    long double mx = -1e100L;

    int M = cand.size();

    for (int i = 0; i < M; i++) {
        for (int j = i + 1; j < M; j++) {
            for (int k = j + 1; k < M; k++) {
                long double a = cand[i];
                long double b = cand[j];
                long double c = cand[k];

                long double val = (a + b + c) / (a * b * c);

                mn = min(mn, val);
                mx = max(mx, val);
            }
        }
    }

    cout << fixed << setprecision(18);
    cout << mn << '\n';
    cout << mx << '\n';

    return 0;
}

//ww ars sfsh wrw


//w rf m proxd searto wer
//w vtsi sfnsfco nsiso 
//1 / xk 
// Dost hsimaknwr
// ww ssihs is
// wrnwo rwsfhsio hsuw