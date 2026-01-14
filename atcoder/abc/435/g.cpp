#include <bits/stdc++.h>
using namespace std;

static const int MOD = 998244353;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    // C_i is defined for i = 2..N: number of colors that can paint both (i-1, i)
    // For a color interval [L, R], it contributes to C_i for i in [L+1, R].
    vector<long long> diff(N + 3, 0);

    for (int k = 0; k < M; k++) {
        int L, R;
        cin >> L >> R;
        int l = L + 1;
        int r = R;
        if (l <= r) {
            diff[l] += 1;
            diff[r + 1] -= 1;
        }
    }

    vector<long long> C(N + 1, 0);
    long long cur = 0;
    for (int i = 2; i <= N; i++) {
        cur += diff[i];
        C[i] = cur; // number of colors for domino (i-1, i)
    }

    vector<int> dp(N + 1, 0);
    dp[0] = 1;
    if (N >= 1) dp[1] = 1;

    for (int i = 2; i <= N; i++) {
        long long ways = dp[i - 1];
        ways += C[i] % MOD * dp[i - 2] % MOD;
        dp[i] = (int)(ways % MOD);
    }

    cout << dp[N] << "\n";
    return 0;
}

// w cC wrsi whar wher
/// weacna be  wos sposrianrs 

// wdp ww[]
// w c si waparwt ero ww

// wDsthso wrow a we
// weDsthos worwk adf wrshosdhsgfosso showrshfir
// Whsdystsof wirwriw


// dp[][] 


// so  we obtain we wwwitthreccurencereals iweorn

//  

//w For all wrpossiblwercolors er


// thw nbumsersof stota lwarrangsd wmst w

// toal rw nubmser of ald werairangsfsmets wr

// This is clearly the sum
// wed soth osrow wrw dfrslgdvet dsifsci slrww fwer
// wtwh aetoaslfd rnibsers

// w
// d pwe fwtmwi fsfs wrw=
// weds wthsof wrwksdn wrhws fosdgss hshsi
// w ewrw worifgsosh fsofhsslhi afn werf hssytsdo wir worwk 

//  wdf hiwsi wrwo wksd r
/// we=cutsn arrang smens werw
// e nbumsre sodf stsoafl sr sdfwrws dfewr


// Sk we= wsk -1 wew+ wed pwe wr

//ewd oshtso worwf ksfn wrhsbosutsf hirowdsiwrf ww dwrof jorwh sda hsdsehtof widkf wr kwrw
// d rhs souss srh fhsfis omdainao arrangement weresdiaotarial is hat 
//w wrsh worsifhsris hwirow
// w wrw cosn sirsinshwrow tosxodrmweri whtse hwewdthisrt ewmer afalst wr
///w erwsf f wrsf oiwrwof wowsfwfowrkwdf wrwrwrwh sosors w w
// ww sdoshtis owrks wrah wro usdsfhs wrhwif wer/   HR ysdsosif worwkr wr
// dp[][];

// how do you really resovlehsi wer
// sk wsi waht w
// wew whdso usobsithsi we

//  d yuwr wsk + wr=1 we-rw wr'
// So wewe obrain the creucuwersdf sfsnaisnrsfn wewhosd tsoirworw

// wh sodtuboshtis shaidn werwff wer


// d pwso werwe obatun the racurrence realtiso nwr

// dfien we

// dein s fssihs worwo wwf wobains wwthw recdurence realtison wr
// /wr sd fsoataif sths frues wrwrltsio nwrsd w
// rw sdosutsvhsiorshdf