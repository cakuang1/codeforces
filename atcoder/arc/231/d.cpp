using namespace std;

using ll = long long;
constexpr ll MOD = 998244353;
constexpr ll INV2 = 499122177;


// wewe sfi hsifrw pobmwelr w



// ww mwhwsd l wrw

// wedf eor sf hwn wr

// wrevow hwlw ws lwur




int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;

        vector<ll> A(N);
        ll total = 1;

        for (ll &a : A) {
            cin >> a;
            total = total * (a % MOD) % MOD;
        }

        // F_i = even count - odd count for the first i positions.
        ll prev2 = 1;          // F_0
        ll prev1 = A[0] % MOD; // F_1

        for (int i = 2; i <= N; ++i) {
            ll largeChoices = (A[i - 1] - A[i - 2]) % MOD;
            ll equalChoices = A[i - 2] % MOD;

            ll current = (
                largeChoices * prev1 +
                equalChoices * prev2
            ) % MOD;

            prev2 = prev1;
            prev1 = current;
        }

        // Odd = (total - F_N) / 2.
        ll answer = (total - prev1 + MOD) % MOD;
        answer = answer * INV2 % MOD;

        cout << answer << '\n';
    }

    return 0;
}

// wvnw wods wrn wiwn soirwer

// werxpfsn wrw

// wthi nwkobousts wrw w


// assuwm rwwt wrs wers wer




// wr wr isnsu werw

// wew wsfww er

// werwh sdf uw rs wrosj wrsss sf wrsh wer

// weod couwetnwe


// wisrsp sisus sfwrlwe r

//  wrwwrw eroyuw er sf wer w ri w 

//  whow msw shss ewr
// () how ma weraalu r sssfltw wr

// if wther wwraeusl wer

 
 werwwwwwodd sou wenr