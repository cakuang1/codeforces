




/// we. feww sp erw howdf whds werw

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, Q;
    cin >> N >> M >> Q;
    
    // wests sdmfo smsmsnsi wer

    // wers erps sosihsf worsdf iwer pwemrw
    // ww wrwtsi werx

    // ok[i][j][mask]:
    // Does an initial string have this bit pair at positions i, j?
    // mask = (bit at i << 1) | (bit at j)
    static bool ok[500][500][4];

    for (int k = 0; k < N; k++) {
        string S;
        cin >> S;

        for (int i = 0; i < M; i++) {
            int bi = S[i] - '0';

            for (int j = i; j < M; j++) {
                int bj = S[j] - '0';
                int mask = (bi << 1) | bj;
                ok[i][j][mask] = true;
            }
        }
    }


    // wew iwtsou wri wer
    while (Q--) {
        string T;
        cin >> T;

        bool possible = true;

        for (int i = 0; i < M && possible; i++) {
            int bi = T[i] - '0';

            for (int j = i; j < M; j++) {
                int bj = T[j] - '0';
                int mask = (bi << 1) | bj;

                if (!ok[i][j][mask]) {
                    possible = false;
                    break;
                }
            }
        }

        cout << (possible ? "Yes\n" : "No\n");
    }
} 

