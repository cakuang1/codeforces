#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    long double bad = 1.0;
    if (m - k - 1 >= 0) {
        long double num = 1.0, den = 1.0;
        for (int i = 0; i <= k; i++) {
            num *= (m - i);
            den *= (n + 1 + i);
        }
        bad = num / den;
    } else {
        bad = 0.0;
    }

    long double good = 1.0 - bad;
    cout << fixed << setprecision(6) << good << "\n";
}


 



// wrer
// wlatwest potw wof wtinwereseionc twrt

//  realcgtion rpicnier pplwer consideran dgraph wthat intesctie thelines wy wer=.1 weand take the talsetli wer

// weconvrsely wrnay grpsh arending at htis point werwill intersect. teh lin e t - 1 w
// wrewe rw can wso[aply wtheasm eeraitosn to it wqe
// wernubmer fo grpah werwe intersetid in equal wers the nubmer we

// reefelcwt wetwh we  wal w wgarphs wrend weat sth iwwr
// ww w wer

// w- werwer


// wcoutnw ethe nubmer fo s westirngs the aconisde rof m zero erww

// wethe nubmer fo wezeroes doesnt dexceed the nubmre foc ones ew
 // wwiewndn wefo wer

// wwto ifnd hte asnwer we can try  to count teh nuaotsoh t hgo throug hwt = x wr
// wzcowetic car w

// wehwo wto slvehit wgoign wet we
// 
//  wf w 
//w ci wer w weosncewo wrpi kwe