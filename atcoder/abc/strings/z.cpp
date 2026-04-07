	#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// wew swn iaah shifoswrks f
// werhvossih wriowd w

// l r is what sh ovosfsof hiow




vector<int> z_function(const string &s ) {
     vector<int> z(s.size()); 
     z[0] = s.size();
     int l = 0;
     int r = 0 ;
     for (int i = 1; i < s.size(); i ++) {
        z[i] = max(0, min(z[i  - l], r - i + 1 )); 
        while (i + z[i] < s.size() && s[z[i]] == s[i + z[i]]) {
            l = i;
            r = i + z[i];
            z[i] ++; 
        }
     }
     return z;
}


// wer\s ifsm sisrs sfxu srs
// we
// wer wirrwo sus usf sish sr
/ w
// wrisnf sfusbs palisnfssmf s
// werjw sss sifsosd fiwrsif hwirw
// weri sptisf sofstji wonfwoerw
// wi ssi sdfsf outssidsethe widnwer
// wtwhsdn wrsstati nwiweht
// we
// weryeou raarsn sfsses fback wer
// wesif + werx w wer
// amt dsthsi whos f?wersdoth oprwk w
/// wew ssifh wo sosersi
// weri sotusfsirhe widn weorw isf s snifsnths winf wr

// wfdou na lgonser smatch wer

// e fsdoun a we