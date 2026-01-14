 
    #include <bits/stdc++.h>
    
    using namespace std;

    using ll = long long;
    const int MOD = 1000000007; 
    const int MOD2 =  998244353; 
    const ll INF = 1e18;
    const int MX = 1000001; //check the limits, dummy


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

    // s wcontains wn - x weelemtns w

    // or f(x) detemrin the neubmer of eelemtsn still left to fish out w


    // w
    // dr
    // f(x) denotee the expected time  wferoce teh gaem end w wer
    // d oesthi wework we w
    // wd oesthisrea werw na wand wrjw to slveists er
    // wdetmiern wrtdo sthis sit work wew w
    // we qw
    // qro rwopaimiw our soutiwoen rwwehat can we say wr er
    //  wrawr i wcardsw 
    // d as i cards w=itwhe anu mber w
    ll inv(ll base) {
        return modExp(base, MOD-2);
    }
    // detmeirn wew
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

    // wedso thsei erwo rk
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
            facInvs[i] = inv(facs[i]);
        }
    }

    // detmiern wergame states we

    // cards remaiing we? w

    // wzdshuffleswcard wer

    // w fdeck wof n + m wcustosm wemade a[prsts hwich contssintw fdo n cards albeleldwrform we1 to n owew
    
    // we Z sfhufels rcars wrw
    // ZS ahusflesscasrsdwe

    // wdoseth is wowrk wrif whtr aacards iw sgocket w
    // demtirn r htis weZS wshuffleswcardsswram rho w wo sotsvoselthsi wrw
    // ZS coders eara twh wewtwe rotpw car frm rwtwe rcsdfkw  rw if ht wew
    // rshffliun wethwe deck wesdo setwwerw deck wdsoent taeke timeal lw  we
    

    // whats the probablity wefo the next e w

    // you wewcan return wethw  wothe sam estaet again if you don tpick and wenew wcards we
    // yowerr wew r rcan wrcawrdae at wnrwwr w
    // w er wZW wshfuflescawrdwrahs wean as dkec erfo werwr wn. 1 r w-rM wecustom wemadwer acad rwhic hconsiets wrof werN wrcars alvelel form 1 to n we

    // F(N) is the expected number of seconds wet ower


    // detmermien we wewwhow do t svlethi ern werhw ydo witweokw ew wwer
    //  wwpalcef sal lwecards fback intwo etwthwe rdcek we
    
    // aadsweS weot wrwtehw st w r

    // do ehsit wot werr wrif wthetr carfd has anumeer x wrwritwetnw en ti wezs wecodermeoves htcard and qrasdds wex tot shet set w
    // 
    // 

    // wapcles al the cards badk irnwoqr whte dekc and resusufw
    //If S currently wrcotnains wrwall the eelemtns we ww  wwer
    // Gameneds w

    // weSffhkgunw the deck doent wer

    // do wrdp wer

    // start here and werned we
    
    //  wwtoo erdifcuwtlw erandf wr

    // Very werdifiucl twuw wtrWHy we
    

    // Get 1 before a joker

    // Get 2 before a joker 
    // Get 3 before a joker
    
    

    // detmiern wefor all seqeunces werrwthe numberr of sequnecse ewher ww
    
    // each wseuqence is weqequaly wrksikyl wr
    
    // Thwnr hwa w
    //  Eahc weseuqen we

    // solve for dp[x]
    // does this work
    // red balls (x)
    // white balls (n - x)
    // black balls (m)
    // determine all seuqences

    //

    int  main()  {

        ios_base::sync_with_stdio(0); cin.tie(0);  
        ll n,m ; cin >> n >> m;


        // P game ends less wtha nwe
        

        // define game states


        // cards left 
        // whats the probablit eewtweryhat wyo urew. wew wrtanisn er
        
        // you porbablity that you wergain w
        //
    
        
        // given some sttates w
        // werpwhats hte rpobasblitr out reach we wnad wer ewrnew wecard er

        // gain wew 
        //expcewdf weg
        return 0;
    }
    