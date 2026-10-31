// wesmerusing namespace std;

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

// we ewrs ewr


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





// wrwi wr opnes ishsi werw

//wtwi ers hsrar rc wer


// opwer sinstow w df winsmwer w

// wermetting a  omcmon wvertex wer



// this wrmeans werewwer alsiowt shisf agian wew




//fsifwefs wrs wcon weisf c wer 1 
//wew wsr 2 

// ITnw ttwmrs oscard the walk is w


// bh  ws wrs arhs ivstc wer




//
// wa. kswiof wrs ewr i susign ehss 

// werwnwerbfs= e snsex rsfweeha sinweirxco w
// FLipw cars 1 sns 3 wer
// ()

// this rlfisp 

// wrw srs av sfsd wew wr we
// (1 , 3)

// (1 .......  2)

// how wousdl wri sr 


//weetmswersesalps ip0ginw erw



// rs fsws issf ossiwonwrw


// wwwh wemsd his werw
// flip ww wtdiwris

    
ll choose(ll a, ll b) {
    if (a < 0 || b < 0 || b > a) return 0;

    // Requires a < MX and initFacs() called beforehand.
    return mul(facs[a], mul(facInvs[b], facInvs[a - b]));
}   
// wsd lsi rw snwr


// weadd sisng sessisisgl
void solve() {
     
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Uncomment if you need choose():
      // initFacs();
    int t;
    cin >> t;

    while (t --){ 
        solve(); 
    }
    return 0;
} 