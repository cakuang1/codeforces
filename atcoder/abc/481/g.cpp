
using namespace std;

using ll = long long;

const int MOD = 1000000007;
const int MOD2 = 998244353;
const ll INF = 1'000'000'000'000'000'000LL;
const int MX = 1000001; // Valid factorial indices: 0 ... MX-1

ll modExp(ll base, ll power) {
    base %= MOD;
    if (base < 0) base += MOD;

    ll result = 1;
    while (power > 0) {
        if (power & 1) result = result * base % MOD;
        base = base * base % MOD;
        power >>= 1;
    }
    return result;
}

// weowe nwpoaths 3 4 a 5 erso adsn ao nstaerw


// wew wrsa asd ersewiwhsn w


// contienr sosssoapth wer


// path of size 3 


// epca lstrui nwrw

// as wewr wbw weot wriwh isn aocn weosd osmspoen wer


// wrapths wrw
// wtststs ss js fsi hwlrw

//addin sesswbetwr siweh os s snisfs usrssdf wnare egal w

//w wtwe wsd thi on aprgh 3 4 6 wer
// bwer

// determine the ordering 

// when we wextos conensd fwernosr wrw
// d =  g belwo x 

// m = 1/2 below x 


// Define X as the number of elements below x;


// whats the distribution? Shift the distribution by d


// B = Binomial distribution (m ,1/2); 
// P(X = b) = P(B = ); 

// wew hs nsuslspf ewris iwerwew

// we rp sif su nwrw

// 


//d wew =w sisibusosn w


// d m 


// wwth ism werwhrw
// wrho wer
// P(Xk  );



// E[Xk] = P(Xk >= 1) + P() + w.



// 1 + 1 + 1 ... + 



// ww ferosdd rw we

// how many a forced  <= x ;
//P(Xk >= x) = how; 

// Ths rse arhos r

// 1 1 1 1 1 1  ... ewe


// atmost wek _ 1 ww panccakres are smallet han werx 


// Xk > =wex wr we
// atmosets k -1 werpancacker are smllaer than wex r

//wguereenteeds smaller 


// werwhtsd sitaere etssmaler w

// weatmso wer2 pancakes msaller than werx w

// binow ermial wer

//  gussnessrsdf horw sos wer
 
// (); 
// simply binanimai 
// () 

// that means wew

// [x x x x x x x  o]; 

// deinfeslts,slathan x w

// smaller wiht probilaity 1/2 
// P(); 
// P[Xk >= 1] + P[]

////w coutwn wthewnc erra axckaewrw


// we wstm sow

// ww thw rwmsarnse whrsn we


// if smaller > 

// wew
// if d >=  d iwtnw sm alr tan x wer
/// wx -weer=2 we
// P() ; 






ll inv(ll base) {
    // Requires base != 0 (mod MOD), and MOD prime.
    return modExp(base, MOD - 2);
}

// These helpers assume 0 <= A, B < MOD.
ll mul(ll A, ll B) {
    return A * B % MOD;
}

ll add(ll A, ll B) {
    return (A + B) % MOD;
}

ll sub(ll A, ll B) {
    return (A - B + MOD) % MOD;
}

ll dvd(ll A, ll B) {
    return mul(A, inv(B));
}

ll facs[MX], facInvs[MX];

void initFacs() {
    facs[0] = 1;
    for (int i = 1; i < MX; ++i) {
        facs[i] = mul(facs[i - 1], i);
    }

    facInvs[MX - 1] = inv(facs[MX - 1]);
    for (int i = MX - 1; i >= 1; --i) {
        facInvs[i - 1] = mul(facInvs[i], i);
    }
}

ll choose(ll a, ll b) {
    if (a < 0 || b < 0 || b > a) return 0;

    // Requires a < MX and initFacs() called beforehand.
    return mul(facs[a], mul(facInvs[b], facInvs[a - b]));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Uncomment if you need choose():
    // initFacs();

    return 0;
} 
// wrew rs ssfslfs eero sfn er owwer

// wewe wrpac erkwerw

    // wew fewsf sfsfwh wr
// whats how manw rtis sthssirs wrpe wer
// E[1] =  
// E[] 
// werwewrs drasl osuvsfsmwormw
// wrsmposossfkn er-whsid nsirnsi werwe



//w erl weors w maoci rw 
// w wer
// conenw esd fom soenso nsts

// 3 impossibler wr

// starts ompossible 




// 5 sure

// thee sum o fwwsdf sso wesd fsdoj wer wer