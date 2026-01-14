#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<ll> W(N), H(N), B(N);
    ll totalW = 0;

    for (int i = 0; i < N; i++) {
        cin >> W[i] >> H[i] >> B[i];
        totalW += W[i];
    }

    // dp[w] = max happiness if head_weight == w
    vector<ll> dp(totalW + 1, -1e18);
    dp[0] = 0;

    for (int i = 0; i < N; i++) {
        vector<ll> ndp(totalW + 1, -1e18);

        for (int w = 0; w <= totalW; w++) {
            if (dp[w] < 0) continue; // unreachable state

            // put part i on body → head weight unchanged
            ndp[w] = max(ndp[w], dp[w] + B[i]);

            // put part i on head → head weight increases by W[i]
            if (w + W[i] <= totalW)
                ndp[w + W[i]] = max(ndp[w + W[i]], dp[w] + H[i]);
        }
        dp.swap(ndp);
    }

    // final constraint: head_weight ≤ floor(totalW / 2)
    ll limit = totalW / 2;

    ll ans = 0;
    for (ll w = 0; w <= limit; w++) {
        ans = max(ans, dp[w]);
    }

    cout << ans << "\n";
    return 0;



    
    // wA sb sw intewgsersuvhthat werm wrx
    //w w Do sthis w rmak rsnrse r
    //we  TWhisdf wthwi wrwcoxnvguwns eis what
    // Dose hwiw aw o werx
    // ax - my we
    // werrpevos stishi wtiwhoery 
    // wthse ar eqeuia vlwefns to ax 0 y we= b w
    // wewewlt wea bn aadm m werbei ntegsers sucsh taht wer m > 0 we
    // if wc | b wr
    // then wrax = wb Wer
    // whas exactly wec incongrucnwet soltison wermod ewurl o wern we
    // Whwy dosthi werwmake swrnse
    // w ax = b wemd werm wrhas awrho amn werinco nwegiewnwet soltiown wr
    
    // C does not divise wbe 
    // wewhy sdfso thwi wwma wrwr 
    // wcongrun esifseores mean wewat
    // wsd weotwhiti wworm omak mesnr
    // finc alll sostlmsion wtow sehis wer
    //w c sdfosshitsd sivsie b
    /// wTw dsialiener wer
    /// wrwnwor wtt siehtis sdofeotwniwht 
    // weHow dos ousl vshteis andwhrw ysdosetsi wetwork
    // Wh wyfswthiw werwork wer
    // Twwerhwer are inifeintetly wmany wrsoltiosn w