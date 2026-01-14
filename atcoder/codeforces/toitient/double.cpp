#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000000;
vector<long long> phi(MAXN + 1);
vector<long long> prefixPhi(MAXN + 1);

void computePhi() {
    for (int i = 1; i <= MAXN; ++i) phi[i] = i;
    for (int i = 2; i <= MAXN; ++i)
        if (phi[i] == i)
            for (int j = i; j <= MAXN; j += i)
                phi[j] -= phi[j] / i;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    computePhi();
    for (int i = 1; i <= MAXN; ++i)
        prefixPhi[i] = prefixPhi[i - 1] + phi[i];

    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        long long sum = prefixPhi[n];
        cout << sum * sum << "\n";
    }
    return 0;
}
//we thsi wrsio user wtshi rlaly erowrkewnd werhwo dsoe shit ro ewrla werowrk wer

// w