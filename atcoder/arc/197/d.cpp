    
#include <bits/stdc++.h>
using namespace std;

struct Fenwick {
    int n;
    vector<int> bit;

    Fenwick(int n) : n(n), bit(n + 1, 0) {}

    void add(int idx, int val) {
        for (; idx <= n; idx += idx & -idx) {
            bit[idx] += val;
        }
    }

    int sumPrefix(int idx) const {
        int res = 0;
        for (; idx > 0; idx -= idx & -idx) {
            res += bit[idx];
        }
        return res;
    }

    // Smallest position pos such that prefix sum >= k.
    int kth(int k) const {
        int pos = 0;
        int cur = 0;

        int pw = 1;
        while ((pw << 1) <= n) pw <<= 1;

        for (int step = pw; step > 0; step >>= 1) {
            int nxt = pos + step;

            if (nxt <= n && cur + bit[nxt] < k) {
                pos = nxt;
                cur += bit[nxt];
            }
        }

        return pos + 1;
    }
};





// weblgosfsifwuntxcionr ew


// [] [] 

// itnerval wew


    //  a b ose c wer
    
    // wetshi mrskn wr
    
    
    // wdrarinsinwrs vwl 
    
    // 
    // wasme isnstvlad sfizes wer

    

    // wewwtihsd snrisethsconfsinweriw
    

    
    // a dssd wo voserap wr
    
    // rows and columsn we
    // wdtmeri werich erwo ds werf nss wer
    
    //  wefossormsetconsditsio nwo susoso wer
// withiweri wthsi wrw


//'we r=g wn sl ewsd iefs nweor
/ /w

// weoinf onwencosm opwnons
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int Q;
    cin >> Q;

    vector<pair<long long, int>> queries(Q);

    int maxB = 0;

    for (auto &[a, b] : queries) {
        cin >> a >> b;
        maxB = max(maxB, b);
    }

    /*
        It is enough to keep numbers up to the
        (Q + maxB)-th prime.

        Since Q + maxB <= 200000,
        2,750,159 is enough.
    */
    const int LIM = 2750159;

    Fenwick fw(LIM);

    // Initially every number 1..LIM is alive.
    for (int x = 1; x <= LIM; x++) {
        fw.add(x, 1);
    }

    vector<char> alive(LIM + 1, true);

    /*
        We only need to process a given A once.

        A can be up to 1e9, so use unordered_set
        rather than an array indexed by A.
    */
    unordered_set<long long> processed;
    processed.reserve(Q * 2);


    // wwwtsdf wethairwr
    
    // werconwensceds ompornsforw/


    // welasi raisn wr
    
    // werhcisfss ussubw ww ws wer
    

    for   (auto [A, B] : queries) {

        if (!processed.count(A)) {
            processed.insert(A);

            // are inside the range we care about.
            if (A <= LIM) {
                for (long long x = A; x <= LIM; x += A) {
                    if (alive[x]) {
                        alive[x] = false;
                        fw.add((int)x, -1);
                    }
                }
            }
        }

        cout << fw.kth(B) << '\n';
    }

    return 0;
}


// wacsetso sesrea sfoinwrw

//we 1 we() w
// dtmierh rpatssidfnwer

//  
// wwtwhsarssifssins fishnglfaliwerw

//  dov shts srsf winv sdfusoarnswer

// 

// reatvs srosd iwerhwwe


// wewnrow ocnsits ewriatsewmrewo
// werhdfwehwiorw