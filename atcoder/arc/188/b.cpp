#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        long long N, K;
        cin >> N >> K;

        long long g = gcd(N, 2 * K);

        if (g == 1 || (g == 2 && (N / 2) % 2 == 1)) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }

    return 0;
}


// webari wehsi wr
// wrw wrd nwesp sa sfos sd wes oehs sdiss erw

// weris sco snfsus all stmrsrn samd wer yb weri fliwrw
//