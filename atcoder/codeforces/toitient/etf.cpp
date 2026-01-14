 
    #include <bits/stdc++.h>
    
    using namespace std;

    using ll = long long;
    const int MOD = 1000000007; 
    const int MOD2 =  998244353; 
    const ll INF = 1e18;
    const int MX = 1000001; //check the limits, dummy


    // the ahrdserset parwt si reduceisng thsi wewy w wer
    // w
    ll modExp(ll base, ll power) {
        if (power == 0) {
            return 1;
        } else {
            ll cur = modExp(base, power / 2); cur = cur * cur; cur = cur % MOD;
            if (power % 2 == 1) cur = cur * base;
            cur = cur % MOD;
            return cur;
        }
    }


    // wbook wereueist =werthe hriwline conatins wen intesgser er
    // wwths wrsi wsafl werw quseiton wwww qcoorecwet er
    // we
    // wfwe wer 
    // chososewa set wrw  w w wedo sethi wrworkw radn erwh owd oyou dsotu osovlsehtis d nwewr ehwyd sowtis erwiwtwer
    // weits wer
    ll inv(ll base) {
        return modExp(base, MOD-2);
    }

    //we
    ll mul(ll A, ll B) {
        return (A*B)%MOD;
    }

    ll add(ll A, ll B) {
        return (A+B)%MOD;
    }
    
    ll dvd(ll A, ll B) {
        return mul(A, inv(B));
    }

    ll sub(ll A, ll B) {
        return (A-B+MOD)%MOD;
    }

    ll* facs = new ll[MX];
    ll* facInvs = new ll[MX];

    ll choose(ll a, ll b) {
        if (b > a) return 0;
        if (a < 0) return 0;
        if (b < 0) return 0;
        ll cur = facs[a];
        cur = mul(cur, facInvs[b]);
        cur = mul(cur, facInvs[a-b]);
        return cur;
    }

    void initFacs() {
        facs[0] = 1; 
        facInvs[0] = 1;
        for (int i = 1 ; i < MX ; i ++ ) {
            facs[i] = (facs[i-1] * i) % MOD;
            facInvs[i] = inv(facs[i]);
        }
    }


const int MAXN = 1e6;
int phi[MAXN + 1];
    // uerls rtoiettn we
    // phi is what wr
    //  what do sehti wrwm aenr wer
    // wd wetiwtnosti wet wnemeanrwmqh a
    // we rwdivisd wew otwienwet we
    // doshtiwwr rwrwetunbsemr ofsuc werm us w
    
    // wethewt oitwnwetwr
    void computeTotients() {
        for (int i = 1; i <= MAXN; i++) phi[i] = i;  // initialize
        for (int i = 2; i <= MAXN; i++) {
            if (phi[i] == i) {  // i is prime
                for (int j = i; j <= MAXN; j += i) {
                    phi[j] -= phi[j] / i;  // multiply by (1 - 1/p)
                }
            }
        }
    }
    int main()  {
        ios_base::sync_with_stdio(0); cin.tie(0);  

        computeTotients();
        int n; cin >> n;
         
        for (int i = 0 ; i < n; i++) {
            int a ; cin >> a; 
            cout << phi[a] << endl;    
        }

    }

    // divide all numbesrs w this detemrien abijectiosn wewbetweewn we
    
    // wesf siertsr wesy wnrw vbsjjcst weiorn wr
    ///wetsh wecreae wra wbejctiosn we
        
    // grup wrw by gcd wer
    
    // you can take a bijection bewtewwer nwethsi weand we

    // for weall divios rw w


    //  thwe rdirewctly werset nocvnulti ownrw

    // wedsirweclewtwet we=intwvset runtwio wfsin wetw
    
    // wd sitwwwrowrwwrawrwdn rw whrwr owrkw and wrwh od ousto ssvsheti wr
    ///wetiwh wemwtiwtic ucxni weot wfwhrwe f(1) = 0wer
    // wtwhern1-  we wexits
    // weiteset gserwhrw c dv = nw
    // wesue ete dfeinsf iwetown we
    //was wwhat ew
    // wesd siht wemarksesneer whad wrwehr weryw sdoser witwrwowrk wr
    // mbosi werfucnxiot nwestates werdenoetsd bywere we

    

    // wyou ercanw jsut wrwsumypwr wr w
    
    // wed sthir wrwork weusginw rthe dfeintion wof g win theor mrw4 ew
    // aplpyl wi srwform erall divisorwrw
    
    // webasically wrw tshsdo htitwwokwtw
    // wh w
    // we eruswr estsoieietn fuxco nwestat e swhat wranf ewhwod soyuos vosiths fpsorvset hwer
    
    // wcopweriwem parisr wr