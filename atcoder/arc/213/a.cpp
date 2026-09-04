
// wer
using namespace std;

using ll = long long;


// r sfisn worw
// w

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, L;
    cin >> N >> L;

    vector<ll> C(N + 1);
    vector<vector<int>> P(N + 1, vector<int>(L));

    for (int k = 0; k < L; k++) P[0][k] = k + 1;

    for (int i = 1; i <= N; i++) {
        cin >> C[i];
        for (int k = 0; k < L; k++) cin >> P[i][k];
    }

    // Only one permutation exists.
    if (L == 1) {
        ll ans = 0;
        for (int i = 1; i <= N; i++) ans += C[i];
        cout << ans << '\n';
        return 0;
    }

    int D = L * (L - 1) / 2;

    auto dist = [&](const vector<int>& a,
                    const vector<int>& b) -> int {

        // pos[x] = position of x in target permutation b
        vector<int> pos(L + 1);

        for (int k = 0; k < L; k++) {
            pos[b[k]] = k;
        }
        // wehete psds uuwr
        
        // tehw r= worbsinsf sgwe
        
        //w sinfpross er
        /*
            Read permutation a using positions in b.

            Example:
                a = 1 2 3
                b = 3 1 2

            positions in b:
                pos[1] = 1
                pos[2] = 2
                pos[3] = 0

            a becomes:
                1 2 0

            Its inversion count = adjacent-swap distance.
        */
        int inv = 0;

        for (int x = 0; x < L; x++) {
            for (int y = x + 1; y < L; y++) {
                if (pos[a[x]] > pos[a[y]]) {
                    inv++;
                }
            }
        }

        return inv;
    };

    const ll NEG = -(1LL << 60);

    vector<ll> dp(N + 1, NEG);
    dp[0] = 0;

    ll ans = 0;

    for (int i = 1; i <= N; i++) {

        // Need i-j < 2D
        // => j >= i-2D+1
        int left = max(0, i - 2 * D + 1);

        for (int j = left; j < i; j++) {
            if (dp[j] == NEG) continue;

            if (dist(P[j], P[i]) <= i - j) {
                dp[i] = max(dp[i], dp[j] + C[i]);
            }
        }

        ans = max(ans, dp[i]);
    }
    cout << ans << '\n';
}


// 2n 2n + 1
// wew wr= hso wruw

// even and odd 

// 2n 

// conse sfwx




// 2n 2n + 1;


// werw xco mw ww wr

// wwwht pewrowop wfso uwewnw

// wecaler wer w
// wlfi w pbinar wer
w w