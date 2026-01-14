#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n), freq;
    int MX = 0;
    for(int i = 0; i < n; i++){
        cin >> a[i];
        MX = max(MX, a[i]);
    }

    // 1) Smallest-Prime-Factor sieve up to MX
    vector<int> spf(MX+1, 0);
    for(int i = 2; i*i <= MX; i++){
        if(!spf[i]){
            for(int j = i*i; j <= MX; j += i)
                if(!spf[j]) spf[j] = i;
        }
    }
    for(int i = 2; i <= MX; i++){
        if(!spf[i]) spf[i] = i;
    }

    // 2) For each prime p, we record:
    //    count_p = how many a[k] are divisible by p,
    //    small_p = smallest exponent among those a[k] divisible by p,
    //    second_p = second-smallest exponent among those.
    vector<int> count_p(MX+1, 0),
                small_p(MX+1, INT_MAX),
              second_p(MX+1, INT_MAX);

    // Factor each a[k]
    for(int x : a){
        // factor x into (p,e) pairs
        // we collect them in a temp vector to avoid counting a prime twice
        vector<pair<int,int>> facs;
        while(x > 1){
            int p = spf[x], e = 0;
            while(x % p == 0){
                x /= p;
                e++;
            }
            facs.emplace_back(p,e);
        }
        // update statistics for each prime divisor
        for(auto &pr : facs){
            int p = pr.first, e = pr.second;
            count_p[p]++;
            // insert e into the two-smallest structure
            if(e < small_p[p]){
                second_p[p] = small_p[p];
                small_p[p] = e;
            } else if(e < second_p[p]){
                second_p[p] = e;
            }
        }
    }

    // power products wrthew w
    ll answer = 1;
    for(int p = 2; p <= MX; p++){
        if(count_p[p] == 0){
            // p never appears => exponent=0
            continue;
        }
        int zeros = n - count_p[p];
        int exp; 
        if(zeros >= 2){
            // at least two zeros => second smallest exponent = 0
            exp = 0;
        } else if(zeros == 1){
            // exactly one zero => second smallest = smallest among positives
            exp = small_p[p];
        } else {
            // no zeros => second smallest among positive exponents
            exp = second_p[p];
        }
        // multiply p^exp into the answer
        while(exp--) answer = answer * p;
    }

    cout << answer << "\n";
    return 0;
}
