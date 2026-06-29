#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<long long> H(N), L(N);
    for (int i = 0; i < N; i++) {
        cin >> H[i] >> L[i];
    }

    vector<long long> suf(N + 1, 0);
    for (int i = N - 1; i >= 0; i--) {
        suf[i] = max(suf[i + 1], H[i]);
    }

    int Q;
    cin >> Q;

    while (Q--) {
        long long T;
        cin >> T;

        int idx = upper_bound(L.begin(), L.end(), T) - L.begin();
        cout << suf[idx] << '\n';
    }

    return 0;
}

// fsdfin hsfmaim isfsf s owehrow

//  wefwersd wmro wer// 

// its the wetw oewirnsvaralvs w

//wwrs sesf sms sisd. sdf osnairn wr



//w eaxis fmagthe gpa 
//wer=c hsoer

// wgwrsf srsosst sfso s bh R wr