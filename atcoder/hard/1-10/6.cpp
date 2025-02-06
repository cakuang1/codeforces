#define _USE_MATH_DEFINES
#include <cstdio>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <complex>
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <bitset>
#include <numeric>
#include <limits>
#include <climits>
#include <cfloat>
#include <functional>
#include <iterator>
using namespace std;

int main()
{
    string s, t;
    cin >> s >> t;
    int n = s.size();
    int m = t.size();

    string ans = "~";
    for(int i=0; i<=n-m; ++i){
        bool ok = true;
        string s2 = s;
        for(int j=0; j<m; ++j){
            if(s[i+j] != '?' && s[i+j] != t[j])
                ok = false;
            s2[i+j] = t[j];
        }
        if(ok){
            replace(s2.begin(), s2.end(), '?', 'a');
            ans = min(ans, s2);
        }
    }
    // double 
    if(ans == "~")
        cout << "UNRESTORABLE" << endl;
    else
        cout << ans << endl;

    return 0;
}
 

