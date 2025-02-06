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
#include <array>
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
#include <memory>
#include <regex>
using namespace std;

int main()
{
    int n, k;
    string s;
    cin >> n >> k >> s;

    vector<pair<int, bool> > v(n);
    int i = 0;
    int j = 0;
    int ans = 0;
    while(j < n){
        while(j < n && s[j] == '1')
            ++ j;
        ans = max(ans, j - i);
        while(j < n && s[j] == '0')
            ++ j;
        -- k;
        if(k < 0){
            while(i < n && s[i] == '1')
                ++ i;
            while(i < n && s[i] == '0')
                ++ i;
        }
        ans = max(ans, j - i);
    } 
    cout << ans << endl;
}
